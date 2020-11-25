#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
   return x * x - 2.0 * cos(3 * x + 1.0);
}

double bisection(double a0, double b0)
{
   double m = (b0 + a0) / 2;
   while (abs(0.0 - f(m)) > 0.00001)
   {
      m = (b0 + a0) / 2;
      if (f(m) * f(a0) < 0.0)
         b0 = m;
      else if (f(m) * f(b0) < 0.0)
         a0 = m;
   }
   return m;
}

int main()
{
   cout << "x1: " << bisection(-1.0, 0.0) << endl;
   cout << "x2: " << bisection(0.0, 1.0);
}