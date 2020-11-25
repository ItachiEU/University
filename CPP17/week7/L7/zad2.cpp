#include <bits/stdc++.h>

using namespace std;

random_device rd;
mt19937 mt(rd());

void uni(double a, double b, string fileName)
{
   ofstream out(fileName);
   uniform_real_distribution<double> real(a, b);
   for (int i = 0; i < 1000; i++)
   {
      out << real(mt) << endl;
   }
   out.close();
}
void binom(double a, double b, string fileName)
{
   ofstream out(fileName);
   binomial_distribution<int> binom(a, b);
   for (int i = 0; i < 1000; i++)
   {
      out << binom(mt) << endl;
   }
   out.close();
}
void normal(double a, double b, string fileName)
{
   ofstream out(fileName);
   normal_distribution<double> norm(a, b);
   for (int i = 0; i < 1000; i++)
   {
      out << norm(mt) << endl;
   }
   out.close();
}

int main()
{
   uni(0, 10, "uni.csv");
   binom(10, 0.5, "binom.csv");
   normal(5, 2, "normal.csv");
}