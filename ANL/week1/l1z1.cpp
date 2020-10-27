#include <bits/stdc++.h>

using namespace std;

double func(double x)
{
   return 4040.0 * ((sqrt(pow(x, 11.0) + 1.0) - 1.0) / pow(x, 11.0));
}
double func2(double x)
{
   return 12120.0 * (x - sin(x)) / pow(x, 3.0);
}
void func3(int n)
{
   double y0 = 1.0, y1 = -(1.0 / 7.0), cur;
   for (int i = 2; i <= n; i++)
   {
      cur = (1.0 / 7.0) * (69.0 * y1 + 10 * y0);
      cout << "i: " << i << " " << cur << endl;
      y0 = y1;
      y1 = cur;
   }
}
void func4(int n)
{
   double i0 = log(2021.0 / 2020.0), cur;
   cout << "i: 0 " << i0 << endl;
   for (int i = 1; i <= n; i++)
   {
      cur = 1.0 / i - 2020.0 * i0;
      cout << "i: "
           << i << " " << cur << endl;
      i0 = cur;
   }
}
void func5()
{
   double res = 4;
   for (int i = 1; i <= 5000; i++)
   {
      res += 4.0 * (1 + -2 * (i % 2)) / (2 * i + 1);
   }
   cout << res << endl;
}
int main()
{
   cout << func(0.001) << endl;
   for (int i = 11; i <= 20; i++)
      cout << func2(pow(10.0, -i)) << " ";
   cout << endl;
   func3(50);
   cout << "======================================" << endl;
   func4(20);
   func5();
}