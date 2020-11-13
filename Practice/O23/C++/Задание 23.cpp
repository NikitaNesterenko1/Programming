#include <iostream>
#include <iomanip>  //std::setprecision

#include "sin.hpp"
#include "factorial.hpp"
#include "combinations.hpp"
{
double const PI = 3.1415926;

int main() {
    std::cout << "n\tn!" << std::endl;
    for (int64_t i = 1; i <= 10; ++i) {
        std::cout << i << "\t" << factorial(i) << std::endl;
    }   
    std::cout << std::endl;


}



}
