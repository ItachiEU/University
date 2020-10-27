#include <bits/stdc++.h>

using namespace std;

//l2z7
double weak_a(double x)
{
   return pow(x, 3.0) - sqrt(pow(x, 6) + 2020.0);
}

double better_a(double x)
{
   return -2020.0 / (pow(x, 3) + sqrt(pow(x, 6) + 2020.0));
}
//to do: b, c

double weak_b(double x)
{
   return pow(x, -4) * (cos(x) - 1.0 + (x * x) / 2.0);
}
double fact(int n)
{
   int res = 1;
   for (int i = 2; i <= n; i++)
      res *= i;
   return res;
}
double better_b(double x)
{
   double res;
   double sign = 1.0;
   for (int i = 0; i < 10; i += 2)
   {
      res += sign * pow(x, i) / fact(i + 4);
   }
   return res;
}
double log_base(double base, double x)
{
   return log(x) / log(base);
}
double weak_c(double x)
{
   return log_base(5.0, x) - 6.0;
}
double better_c(double x)
{
   return log_base(5, (x / pow(5, 6)));
}
//l2z8
double fx_weak(double x)
{
   return 4040.0 * ((sqrt(pow(x, 11.0) + 1.0) - 1.0) / pow(x, 11.0));
}
double fx_better(double x)
{
   return 4040.0 / (sqrt(pow(x, 11) + 1.0) + 1.0);
}
//l2z9
double standard()
{
   double res = 2.0;
   for (int k = 1; k <= 90; k++)
   {
      if (k % 10 == 0)
         cout << res << "<- k: " << k << endl;
      res = pow(2.0, k) * sqrt(2.0 * (1.0 - sqrt(1 - pow((res / pow(2.0, k)), 2))));
   }
   return res;
}
double standard_improved()
{
   double res = 2.0;
   for (int k = 1; k <= 90; k++)
   {
      if (k % 10 == 0)
         cout << res << "<- k: " << k << endl;
      res = pow(2.0, k) * sqrt(2.0 * ((pow(res, 2) / pow(2.0, 2 * k)) / (1.0 + sqrt(1.0 - (pow(res, 2) / pow(2.0, 2 * k))))));
   }
   return res;
}

int main()
{
   double x = 10000.0;
   cout << "7.a) " << endl;
   cout << weak_a(x) << "\n"
        << better_a(x) << endl;

   cout << "7b)\n";
   cout << weak_b(0.0) << "\n"
        << better_b(0.0) << endl;
   cout << "7c)\n";
   cout << weak_c(pow(5, 6)) << "\n"
        << better_c(pow(5, 6)) << endl;

   cout << "z8: \n";
   cout << fx_weak(0.001) << "\n"
        << fx_better(0.001) << endl;

   //dziewiate
   cout << "z9: \n";
   cout << standard() << endl;
   cout << standard_improved() << endl;
}