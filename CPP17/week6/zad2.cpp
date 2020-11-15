#include <bits/stdc++.h>
using namespace std;

class Point
{
public:
   string name;
   int x;
   int y;
   int r;
   int g;
   int b;
   Point(string name, int x, int y, int r, int g, int b) : name(name), x(x), y(y), r(r), g(g), b(b){};
   void print()
   {
      cout << name << "  rgb: " << r << " " << g << " " << b << endl;
   }
};
random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> numerki(-256, 0);
uniform_int_distribution<int> literki(static_cast<int>('a'), static_cast<int>('z'));

Point generate()
{
   string name = "";
   for (int i = 0; i < (numerki(mt) + 256) % 10 + 1; i++)
   {
      name += literki(mt);
   }
   int x = numerki(mt) + 128, y = numerki(mt) + 128, r = numerki(mt) + 256, g = numerki(mt) + 256, b = numerki(mt) + 256;
   return Point(name, x, y, r, g, b);
}

int main()
{
   list<Point> l;
   for (int i = 0; i < 17; i++)
      l.push_back(generate());
   for (auto it = l.begin(); it != l.end(); it++)
      (*it).print();

   cout << "\n a) \n";

   l.remove_if([](Point a) {
      return a.name.size() > 5;
   });
   for (auto it = l.begin(); it != l.end(); it++)
      (*it).print();

   cout << "\n b) \n";
   int cwiartka1 = count_if(l.begin(), l.end(), [](Point a) {
      return a.x > 0 && a.y > 0;
   });
   int cwiartka3 = count_if(l.begin(), l.end(), [](Point a) {
      return a.x < 0 && a.y < 0;
   });
   int cwiartka2 = count_if(l.begin(), l.end(), [](Point a) {
      return a.x > 0 && a.y < 0;
   });
   int cwiartka4 = count_if(l.begin(), l.end(), [](Point a) {
      return a.x < 0 && a.y > 0;
   });
   cout << cwiartka1 << " " << cwiartka2 << " " << cwiartka3 << " " << cwiartka4 << endl;

   cout << "\n c) \n";
   l.sort([](Point a, Point b) {
      double ba = 0.3 * a.r + 0.59 * a.g + 0.11 * a.b, bb = 0.3 * b.r + 0.59 * b.g + 0.11 * b.b;
      return ba < bb;
   });
   for (auto it = l.begin(); it != l.end(); it++)
      (*it).print();

   cout << "\n d) \n";
   list<Point> l2;
   auto pos = lower_bound(l.begin(), l.end(), 64.0, [](Point a, double b) {
      double ba = 0.3 * a.r + 0.59 * a.g + 0.11 * a.b;
      return ba < b;
   });
   l2.splice(l2.begin(), l, l.begin(), pos);
   for (auto it = l2.begin(); it != l2.end(); it++)
      (*it).print();
}