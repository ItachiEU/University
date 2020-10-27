#include <bits/stdc++.h>
using namespace std;

int main()
{
   auto p = make_shared<int>(7);
   weak_ptr<int> weak = p;
   if (auto temp = weak.lock())
      cout << (*temp) << endl;
   else
      cout << "expired" << endl;

   p.reset(new int);
   (*p) = 5;

   if (auto temp = weak.lock())
      cout << (*temp) << endl;
   else
      cout << "expired" << endl;
}