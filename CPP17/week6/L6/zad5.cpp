#include <bits/stdc++.h>
using namespace std;

void foo(string a)
{
   do
   {
      cout << a << endl;
   } while (next_permutation(a.begin(), a.end()));
}

int main()
{
   string a = "test";
   foo(a);
}