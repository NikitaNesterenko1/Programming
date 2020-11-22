#include <iostream>
#include <cpp_httplib/httplib.h>
using namespace httplib;
 
// В этой функции формируем ответ сервера на запрос
void gen_response(const Request& req, Response& res) {
  // Команда set_content задаёт ответ сервера и тип ответа:
  // Hello, World! - тело ответа
  // text/plain - MIME тип ответа (в данном случае обычный текст)
  res.set_content("Hello, World!", "text/plain");
}
 
int main(){
  Server svr;                    // Создаём сервер (пока-что не запущен)
  svr.Get("/", gen_response);    // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
  std::cout << "Start server... OK\n";
  svr.listen("localhost", 1234); // Запускаем сервер на localhost и порту 1234
}