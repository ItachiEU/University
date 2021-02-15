
#include <bits/stdc++.h>

using namespace std;

complex<long double> Gamma(complex<long double> z, int n)
{
   complex<long double> ans(1.0, 0);
   for (long double i = 1; i <= n; i++)
   {
      complex<long double> num = pow(1 + 1.0 / i, z);
      complex<long double> den = static_cast<long double>(1) + z / i;
      complex<long double> frac = num / den;
      ans *= frac;
   }
   return ans / z;
}
complex<long double> Gamma_inv(complex<long double> z, int n)
{
   complex<long double> ans(1.0, 0);
   for (long double i = 1; i <= n; i++)
   {
      complex<long double> prod = ((long double)1 + z / i) / exp(z / i);
      ans *= prod;
   }
   long double lambda = 0.5772156649;
   ans *= z * exp(lambda * z);
   return ans;
}

complex<long double> Dzeta(complex<long double> z, int n)
{
   complex<long double> ans(0, 0);
   for (long double i = 1; i <= n; i++)
   {
      complex<long double> one(1, 0);
      ans += one / pow(i, z);
   }
   return ans;
}

complex<long double> DzetaR(complex<long double> z, int n)
{
   complex<long double> ans(0, 0);
   for (long double i = 1; i <= n; i++)
   {
      ans += pow(-1.0, i + 1.0) / pow(i, z);
   }
   return ans / (static_cast<long double>(1) - static_cast<long double>(2) / pow(2.0, z));
}

int main()
{
   complex<long double> z1(3, 2);
   cout << z1 << endl;
   auto test = Gamma(z1, 10000);
   cout << test << endl;
   auto test_inv = Gamma_inv(z1, 1000);
   cout << test_inv << endl;
   cout << test * test_inv << endl;

   complex<long double> z2(2, 0);
   cout << Dzeta(z2, 10000) << endl;

   fstream f;
   f.open("data.txt", ios::out);
   for (long double i = -30; i <= 30; i += 0.01)
   {
      complex<long double> c(0.5, i);
      auto val = DzetaR(c, 1000);
      f << val.real() << " ; " << val.imag() << "\n";
   }
   f.close();

   return 0;
}