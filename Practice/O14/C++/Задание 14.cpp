#include <iostream>
using namespace std;

int main()
{
     long  n, p = 1, count = 1;

    cin >> n;
    if (n == 0)cout << 0;
    else
    {
        while ((p *= 2) <= n)
            count++;
        cout << count;
    }
    system("pause");
    return 0;
}

