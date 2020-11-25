#include <bits/stdc++.h>
using namespace std;

auto moda(vector<int> &test)
{
   unordered_map<int, int> ile;
   for (auto el : test)
      ile[el]++;
   vector<pair<int, int>> res;
   for (auto el : ile)
      res.push_back(el);
   sort(res.begin(), res.end(), [](pair<int, int> a, pair<int, int> b) {
      return a.second > b.second;
   });
   vector<pair<int, int>> result;
   for (unsigned i = 0; i < res.size() - 1; i++)
   {
      result.push_back(res[i]);
      if (res[i + 1].second != res[i].second)
         break;
   }
   return result;
}

int main()
{
   vector<int> test = {1, 1, 3, 5, 8, 9, 5, 8, 8, 5};
   auto t = moda(test);
   for (auto el : t)
      cout << "{" << el.first << ", " << el.second << "}\n";
}