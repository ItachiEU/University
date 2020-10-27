#include <bits/stdc++.h>

using namespace std;

const double pi = 3.14159265359;

double firsta(double x)
{
   return 4.0 * pow(cos(x), 2) - 3.0;
}
double firsta2(double x)
{
   return -16.0 * cos((x + (pi / 6.0)) / 2.0) * cos((x - (pi / 6.0)) / 2.0) * sin((x + (pi / 6.0)) / 2.0) * sin((x - (pi / 6.0)) / 2.0);
}

double firstb(double x)
{
   return (pi / 2.0 - x - atan(1.0 / x)) / pow(x, 3);
}
double firstb2(double x)
{
   return -1.0 / 3.0 + pow(x, 2) / 5.0 - pow(x, 4) / 7.0 + pow(x, 6) / 9.0 - pow(x, 8) / 11.0;
}

int main()
{
   cout << firsta(pi / 6.0) << endl;
   cout << firsta2(pi / 6.0) << endl;

   cout << "==============================\n";

   cout << firstb(0.00000001) << endl;
   cout << firstb2(0.00000001) << endl;

   cout << "==============================\n";
}