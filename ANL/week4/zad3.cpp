#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
   return x - 0.49;
}

void bisection(int n, double a0, double b0)
{
   while (n--)
   {
      double m = (b0 + a0) / 2;
      cout << "m_n: " << m << " |E_n| -> " << abs(0.49 - m) << endl;
      //cout << f(m) << " " << f(a0) << " " << f(b0) << endl;
      if (f(m) * f(a0) < 0.0)
         b0 = m;
      else if (f(m) * f(b0) < 0.0)
         a0 = m;
   }
}

int main()
{
   bisection(5.0, 0.0, 1.0);
}