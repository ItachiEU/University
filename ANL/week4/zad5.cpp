#include <iostream>
using namespace std;

double m_newton(double R, double x, int n)
{
    double ans;
    for (int i = 0; i < n; i++)
    {
        ans = x * (2.0 - x * R);
        x = ans;
    }
    return ans;
}

int main()
{
    cout << "R = 5.0, x0 = 0.39 , 1/R = " << 1.0 / 5.0 << endl;
    for (int i = 1; i < 10; i++)
    {
        cout << "ITERACJI: " << i << " ";
        cout << m_newton(5.0, 0.39, i) << endl;
    }

    cout << "R = 5.0, x0 = 0.25 , 1/R = " << 1.0 / 5.0 << endl;
    for (int i = 1; i < 10; i++)
    {
        cout << "ITERACJI: " << i << " ";
        cout << m_newton(5.0, 0.25, i) << endl;
    }

    cout << "R = 5.0, x0 = 0.1 , 1/R = " << 1.0 / 5.0 << endl;
    for (int i = 1; i < 10; i++)
    {
        cout << "ITERACJI: " << i << " ";
        cout << m_newton(5.0, 0.1, i) << endl;
    }
    cout << "R = 5.0, x0 = -0.1 , 1/R = " << 1.0 / 5.0 << endl;
    for (int i = 1; i < 10; i++)
    {
        cout << "ITERACJI: " << i << " ";
        cout << m_newton(5.0, -0.1, i) << endl;
    }

    return 0;
}