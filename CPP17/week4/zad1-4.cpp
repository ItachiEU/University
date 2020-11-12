#include <bits/stdc++.h>
using namespace std;

vector<double> a;
list<string> b;
set<int> c;

void fill_abc(int n)
{
   random_device rd;
   mt19937 mt(rd());
   uniform_int_distribution<int> dist(0, 25);
   while (n--)
   {
      a.push_back((double)dist(mt) + 0.5);
      b.push_back(string(3, 'a' + dist(mt)));
      c.insert(dist(mt));
   }
}
template <template <typename> class CollectionType, class ItemType>
class Container
{
public:
   CollectionType<ItemType> kontener;
};
void zad1()
{
   // a)
   cout << "a: \n";
   int mini = 4, maxi = 20;
   auto lambda = [mini, maxi](auto el) {
      //using T = decltype(el);
      if (el >= mini && el <= maxi)
         cout << el << " ";
   };
   for_each(a.begin(), a.end(), lambda);
   cout << endl;
   cout << "--------------\n";
   string minS = "c", maxS = "y";
   for_each(b.begin(), b.end(), [minS, maxS](string el) {
      if (el >= minS && el <= maxS)
         cout << el << " ";
   });
   cout << endl;
   cout << "--------------\n";
   for_each(c.begin(), c.end(), lambda);
   cout << endl;
   cout << "-------------------------------------\n";

   //b
   cout << "b: \n";
   int p = 3, k = 4, counter = 0;

   auto lambda2 = [p, k, &counter](auto el) {
      if (counter >= p && (counter - p) % k == 0)
         cout << el << " ";
      counter++;
   };

   for_each(a.begin(), a.end(), lambda2);
   cout << endl;
   cout << "--------------\n";
   p = 3, k = 4, counter = 0;
   for_each(b.begin(), b.end(), lambda2);
   cout << endl;
   cout << "--------------\n";
   p = 3, k = 4, counter = 0;
   for_each(c.begin(), c.end(), lambda2);
   cout << endl;
   cout << "--------------\n";

   //c
   cout << "c: \n";

   auto lambda3 = []<typename Collection>(Collection kontener, typename Collection::value_type sum) {
      for (auto el : kontener)
         sum += el;
      return sum / kontener.size();
   };
   cout << lambda3(a, 0.0) << endl;
   cout << "--------------\n";
   cout << lambda3(c, 0.0) << endl;
   cout << "--------------\n";

   //d
   cout << "d: \n";

   auto lambda4 = []<typename Collection>(Collection kontener, typename Collection::value_type mini, typename Collection::value_type maxi) {
      auto it = kontener.begin();
      pair<decltype(kontener.begin()), decltype(kontener.begin())> res = {kontener.begin(), kontener.begin()};
      while (it != kontener.end())
      {
         if (mini > *it)
         {
            mini = *it;
            res = {it, res.second};
         }
         if (maxi < *it)
         {
            maxi = *it;
            res = {res.first, it};
         }
         it++;
      }
      return res;
   };

   auto test = lambda4(a, *a.begin(), *a.begin());
   cout << *test.first << " " << *test.second;
   cout << endl;
   cout << "--------------\n";
   auto test2 = lambda4(b, *b.begin(), *b.begin());
   cout << (*test2.first) << " " << (*test2.second) << endl;
   cout << endl;
   cout << "--------------\n";
   auto test3 = lambda4(c, *c.begin(), *c.begin());
   cout << (*test3.first) << " " << (*test3.second) << endl;
   cout << endl;
   cout << "--------------\n";

   //e
   cout << "e: \n";

   auto lambda5 = []<typename Collection>(Collection kontener, typename Collection::value_type sum) {
      for (auto el : kontener)
         sum += el;
      return sum;
   };
   cout << lambda5(a, 0.0) << endl;
   cout << "--------------\n";
   cout << lambda5(b, "") << endl;
   cout << "--------------\n";
   cout << lambda5(c, 0) << endl;
   cout << "--------------\n";
}

template <class F, class G, class H>
decltype(auto) compose(F f, G g, H h)
{
   return [=](auto x) { return f(g(x), h(x)); };
}

template <class F, class G>
decltype(auto) po(F f, G g)
{
   return [=](auto x) { return g(f(x)); };
}

int f(int x, int y) { return x + y; }
int g(int x) { return x * 2; }
int h(int x) { return x - 1; }

int f1(int x) { return x * x; }
int g1(int x) { return x + 2; }
int h1(int x) { return x + 2; }

int main()
{
   fill_abc(10);
   zad1();
   //zad2:
   cout << compose(f, g, h)(10) << endl;
   //zad3:
   cout << po(f1, g1)(10) << endl;
   cout << po(po(g1, h1), h1)(10) << endl;
}