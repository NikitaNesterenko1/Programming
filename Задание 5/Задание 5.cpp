

#include <iostream>
 
using namespace std; 

int main()
{
    setlocale(LC_ALL, "Ru");
    
    double x0, v0, t, g, a, s, x;
    g = 9,8;
    
    cout << "x0"; cin >> x0;
    cout << "v0"; cin >> v0;
    cout << "t"; cin >> t;
   
    a = g;
    
    x = x0 + v0 * t - g * t * (t / 2);
    s = x - x0;
   
    cout << "Расстояние =" << s;
}

