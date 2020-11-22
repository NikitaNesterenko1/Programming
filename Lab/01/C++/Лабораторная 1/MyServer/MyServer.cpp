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
}

json get_weather() {
    // Создаём клиент и привязываем к домену. Туда пойдут наши запросы
    Client cli("http://api.openweathermap.org");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    auto res = cli.Get("/data/2.5/weather?q=Simferopol&appid=e77a594c893b3114f6e35c0c3aab4509");
    // res преобразуется в true, если запрос-ответ прошли без ошибок
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
        }
    }
    else {
        auto err = res.error();
        std::cout << "Error code: " << err << std::endl;
    }
}

// В этой функции формируем ответ сервера на запрос
void gen_response(const Request& req, Response& res) {
	// Команда set_content задаёт ответ сервера и тип ответа:
	// Hello, World! - тело ответа
	// text/plain - MIME тип ответа (в данном случае обычный текст)
	res.set_content("Hello, World!", "text/plain");
}
void gen_response_raw(const Request& req, Response& res) {
    //long t = get_time();
    //json w = get_weather();
    res.set_content("{}", "text/json");
}

int main() {
	Server svr;                    // Создаём сервер (пока-что не запущен)
	svr.Get("/", gen_response);
    svr.Get("/raw", gen_response_raw);     // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
	std::cout << "Start server... OK\n";
	svr.listen("localhost", 3000); // Запускаем сервер на localhost и порту 3000
}