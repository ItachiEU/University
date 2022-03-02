#include <bits/stdc++.h>
using namespace std;

int main()
{
   map<pair<int, int>, bool> test;
   test.insert({{1, 2}, true});
   test.insert({{2, 3}, true});
   test.erase({1, 2});
   test.erase({1, 2});
   for (auto el : test)
   {
      cout << el.first.first << " " << el.first.second << " " << el.second << endl;
   }
}