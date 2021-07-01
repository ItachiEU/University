#include <bits/stdc++.h>

using namespace std;

int main()
{
   ios_base::sync_with_stdio(false);

   int a, b;
   cin >> a >> b;

   for (int i = min(a, b); i <= max(a, b); i++)
   {
      cout << i << "\n";
   }
}