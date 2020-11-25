#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 mt(rd());

template <typename Collection>
void permutate(Collection &objects)
{
   int n = objects.size();
   for (int i = 0; i < n; i++)
   {
      uniform_int_distribution<int> uni(i, n - 1);
      swap(objects[i], objects[uni(mt)]);
   }
}

int main()
{
   vector<int> tab(20);
   for (int i = 0; i < 20; i++)
      tab[i] = i;
   permutate(tab);
   for (auto el : tab)
      cout << el << endl;
}