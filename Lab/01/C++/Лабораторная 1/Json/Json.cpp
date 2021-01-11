#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

int main()
{
    // Какой-то JSON в виде строки
    string str =
        R"({
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": null,
  "answer": {
    "everything": 42
  },
  "list": [1, 0, 2],
  "listj": [{"v":123}],
  "object": {
    "currency": "USD",
    "value": 42.99
  }
})";
    // Парсим строку и получаем объект JSON
    json j = json::parse(str);
    // Достаём значения
    double pi = j["pi"];                 cout << "pi " << pi << endl;
    bool happy = j["happy"];             cout << "happy " << happy << endl;
    string name = j["name"];             cout << "name " << name << endl;
    double value = j["object"]["value"]; cout << "value " << value << endl;
    cout << "every " << to_string(j["answer"]["everything"].get<int>()) << endl;
    // Идём по массиву
    for (int i = 0; i < j["list"].size(); i++)
        cout << "list[" << i << "] = " << j["list"][i] << endl;
    // Идём по массиву
    for (int i = 0; i < j["listj"].size(); i++) {
    cout << "listj[" << i << "] = " << j["listj"][i] << endl;
    cout << "listj[" << i << "] = " << j["listj"][i]["v"] << endl;
    }
    // Пустой JSON
    json j2;
    // Заполняем разными данными
    j2["num"] = 1;
    j2["array"] = json::array();
    j2["array"].push_back(1);
    j2["array"].push_back(2);
    j2["object"] = json::object();
    j2["object"].push_back({ "PI", pi });
    j2["object"].push_back({ "exp", 2.71 });
    // Преобразуем в строку и выводим
    std::cout << j2.dump(4);
}