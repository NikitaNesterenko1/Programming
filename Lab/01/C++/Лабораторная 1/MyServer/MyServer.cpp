#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace httplib;
using namespace std;



long get_time (){
    // Создаём клиент и привязываем к домену. Туда пойдут наши запросы
    Client cli("http://worldtimeapi.org");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    auto res = cli.Get("/api/timezone/Europe/Simferopol");
    // res преобразуется в true, если запрос-ответ прошли без ошибок
    if (res) {
        // Проверяем статус ответа, т.к. может быть 404 и другие
        if (res->status == 200) {
            // В res->body лежит string с ответом сервера
            std::string body = res->body;
            std::cout << body << std::endl;
            json j = json::parse(body);
            return j["unixtime"].get<long>() ;
        }
        else {
            std::cout << "Status code: " << res->status << std::endl;
        }
    }
    else {
        auto err = res.error();
        std::cout << "Error code: " << err << std::endl;
    }
    return -1;
}

json get_weather() {
    // Создаём клиент и привязываем к домену. Туда пойдут наши запросы
    Client cli("http://api.openweathermap.org");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    // запрос погоды по часам для 7 дней
    auto res = cli.Get("/data/2.5/onecall?lat=44.96&lon=34.11&units=metric&exclude=current,minutely,daily,alerts&appid=e77a594c893b3114f6e35c0c3aab4509");
    if (res) {
        // Проверяем статус ответа, т.к. может быть 404 и другие
        if (res->status == 200) {
            // В res->body лежит string с ответом сервера
            std::string body = res->body;
            std::cout << body << std::endl;
            json j = json::parse(body);
            return j;
        }
        else {
            std::cout << "Status code: " << res->status << std::endl;
            return json({ "error",res->status });
        }
    }
    else {
        auto err = res.error();
        std::cout << "Error code: " << err << std::endl;
        return json({ "error",err });
    }
}

json get_weather_cach() {
    // из файла вычитываю погоду 
    ifstream fin("weather");
    if (fin.is_open()) {
        string f;
        getline(fin, f, '\0');
        fin.close();
        return json::parse(f);
    }
    else {
        json forecast = get_weather();
        if (forecast["error"].is_null()) {
            ofstream h("weather");
            h << forecast;
            h.close();
        }
        return forecast;
    }
}

json get_weather_hour() {
    // нахождение погоды за час до настоящего
    long t = time(0);
    int k = 0;
    do {
        json w = get_weather_cach();
        if (!w["error"].is_null()) {
            return w;
        }
        json hourly = w["hourly"];
        int s = hourly.size() - 1;
        for (int i = s; i >= 0; --i) {
            if (hourly[i]["dt"] > t) {
                return hourly[i];
            }
        }
        // TODO загрузить новые данные с сервера 
    } while (k++ < 3);
    return json({ "error","нет данных" });
}

void repleas(string& text, string play, string change) {
    size_t position = text.find(play);
    while (position != string::npos) {
        text.replace(position, play.length(), change);
        position = text.find(play, position + play.length());
    }
}

void gen_response(const Request& req, Response& res) {
    // вывод данных в виде html
    json w = get_weather_hour();
    if (!w["error"].is_null()) {
        res.set_content(w.dump(), "text/json");
        return ;
    }
    ifstream fin("tep.html");
    string str;
    getline(fin, str, '\0');
    fin.close();
    cout << str;
    repleas(str, "{hourly[i].weather[0].description}", w["weather"][0]["description"]);
    repleas(str, "{hourly[i].weather[0].icon}", w["weather"][0]["icon"]);
    repleas(str, "{hourly[i].temp}", to_string(w["temp"]));
    cout << str;

	res.set_content(str, "text/html");
}
void gen_response_raw(const Request& req, Response& res) {
    // json
    json w = get_weather_hour();
    res.set_content(w.dump(), "text/json");
}

int main() {
    // запуск сервера 
	Server svr;                    // Создаём сервер (пока-что не запущен)
	svr.Get("/", gen_response);
    svr.Get("/raw", gen_response_raw);     // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
	std::cout << "Start server... OK\n";
	svr.listen("localhost", 3000); // Запускаем сервер на localhost и порту 3000
}