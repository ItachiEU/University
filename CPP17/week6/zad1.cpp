#include <bits/stdc++.h>
using namespace std;

class Person
{
public:
   string name;
   string surname;
   int age;
   double weight;
   int height; //in cm
   void print()
   {
      cout << name << " " << height << " " << weight << endl;
   }
   Person(string n, string sn, int a, double w, int h) : name(n), surname(sn), age(a), weight(w), height(h){};
};

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> numerki(20, 60);
uniform_int_distribution<int> literki(static_cast<int>('a'), static_cast<int>('z'));

Person generate()
{
   string name = "", surname = "";
   for (int i = 0; i < numerki(mt) / 8; i++)
   {
      name += static_cast<char>(literki(mt));
      surname += static_cast<char>(literki(mt));
   }
   int age = numerki(mt);
   double weight = numerki(mt) + 40;
   int height = 135 + numerki(mt);
   return Person(name, surname, age, weight, height);
}

int main()
{
   deque<Person> q;
   for (int i = 0; i < 11; i++)
      q.push_back(generate());

   sort(q.begin(), q.end(), [](Person a, Person b) {
      double bmiA = static_cast<double>(a.weight / (a.height * a.height / 10000.0)), bmiB = static_cast<double>(b.weight / (b.height * b.height / 10000.0));
      return bmiA < bmiB;
   });

   cout << "a) \n";
   for (auto it = q.begin(); it != q.end(); it++)
      (*it).print();

   for_each(q.begin(), q.end(), [](Person &a) {
      a.weight *= 0.9;
   });

   cout << "\n b) \n";
   for (auto it = q.begin(); it != q.end(); it++)
      (*it).print();

   cout << "\n c) \n";
   partition(q.begin(), q.end(), [](Person a) {
      return a.weight < 80.0;
   });
   for (auto it = q.begin(); it != q.end(); it++)
      (*it).print();

   cout << "\n d \n";
   nth_element(q.begin(), q.begin() + 5, q.end(), [](Person a, Person b) {
      return a.height < b.height;
   });

   for (auto it = q.begin(); it != q.end(); it++)
      (*it).print();

   cout << "\n e \n";
   random_shuffle(q.begin(), q.begin() + 5);
   random_shuffle(q.begin() + 6, q.end());

   for (auto it = q.begin(); it != q.end(); it++)
      (*it).print();

   auto it = min_element(q.begin(), q.end(), [](Person a, Person b) {
      return a.height < b.height;
   });
   cout << "Najnizsza: ";
   (*it).print();
   it = max_element(q.begin(), q.end(), [](Person a, Person b) {
      return a.height < b.height;
   });
   cout << "Najwyzsza: ";
   (*it).print();
}