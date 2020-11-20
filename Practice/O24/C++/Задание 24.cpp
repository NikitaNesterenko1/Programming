#include <fstream>
#include <iostream>
#include <iomanip>
#include "json.hpp"
using json = nlohmann::json;

int main() {
    std::ifstream input("in.json");
    json inObject; input >> inObject;
    json outObject;

    for (auto& item : inObject) {
        int userId = item["userId"];
        bool complTask = item["completed"];

        json linkUser;
        json* user = &linkUser;

        for (auto& userFind : outObject) {
            if (userFind["userId"] == userId) {
                user = &userFind;
                break;
            }
        }
        if (user->empty()) {
            outObject.push_back({ { "userId", userId }, { "task_completed", 0 } });
            user = &outObject[outObject.size() - 1];
        }
        if (complTask == true) {
            (*user)["task_completed"] = static_cast <int> ((*user)["task_completed"]) + 1;
        }
    }

    std::ofstream output("out.json");
    output << std::setw(4) << outObject << std::endl;
}