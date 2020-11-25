#include <iostream>
#include <math.h>
using namespace std;

double m_newton(double a, double x, int n)
{
    double ans;
    for (int i = 0; i < n; i++)
    {
        ans = (x / 2.0) * (3.0 - a * x * x);
        x = ans;
    }
    return ans;
}

int main()
{
    cout << "Przedzial x0 : " << sqrt(1.0 / 15.0) << " , " << sqrt(5.0 / 15.0) << "\n";
    cout << "a = 5.0, x0 = 0.30 , 1/sqrt(a) = " << 1.0 / (sqrt(5.0)) << endl;
    for (int i = 1; i < 10; i++)
    {
        cout << "ITERACJI: " << i << " ";
        cout << m_newton(5.0, 0.30, i) << endl;
    }

    cout << "a = 5.0, x0 = 0.50 , 1/sqrt(a) = " << 1.0 / (sqrt(5.0)) << endl;
    for (int i = 1; i < 10; i++)
    {
        cout << "ITERACJI: " << i << " ";
        cout << m_newton(5.0, 0.50, i) << endl;
    }

    return 0;
}