#include <bits/stdc++.h>
using namespace std;

string dodawanie(string a, string b)
{
   string suma;
   int reszta = 0;
   for (int i = a.size() - 1; i >= 0; i--)
   {
      int tmp = (a[i] - '0') + (b[i] - '0') + reszta;
      if (tmp > 9)
      {
         reszta = 1;
         tmp -= 10;
      }
      else
         reszta = 0;

      suma += tmp + '0';
   }
   suma += (char)reszta;
   reverse(suma.begin(), suma.end());
   return suma;
}

int main()
{
   string a, b;
   cin >> a >> b;
   cout << dodawanie(a, b) << endl;
}