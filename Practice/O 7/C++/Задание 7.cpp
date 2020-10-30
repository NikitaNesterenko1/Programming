#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double   S, D;
    cout << "D="; cin >> D;

    if (D == 1) {
        double a, b, c, p;
        cout << "a="; cin >> a;
        cout << "b="; cin >> b;
        cout << "c="; cin >> c;
        p=((a+b+c)/2);
        S = sqrt(p * (p - a) * (p - b) * (p - c));
     
        
    }
    
    else {
        double x1, x2, x3, y1, y2, y3 ;

        cout << "x1 y1: "; cin >> x1 >> y1; 
        cout << "x2 y2: "; cin >> x2 >> y2 ;          
        cout << "x3 y3: "; cin >> x3 >> y3 ;        
        S = (fabs(((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))))/2;
    }
    cout << "S=" << S;
}


