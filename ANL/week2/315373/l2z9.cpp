#include <bits/stdc++.h>
using namespace std;

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
   cout << fixed;
   cout << setprecision(9) << standard() << endl;
   cout << setprecision(14) << standard_improved() << endl;
}