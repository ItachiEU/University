//Filip Komorowski
//315373
//KPO

#include <bits/stdc++.h>

using namespace std;

int main()
{
   ios_base::sync_with_stdio(false);
   long long int a, b;
   cin >> a >> b;
   while (a % 2021 != 0)
      a++;
   for (int i = a; i <= b; i += 2021)
   {
      cout << i << " ";
   }
}