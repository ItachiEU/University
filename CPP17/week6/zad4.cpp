#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv)
{
   ifstream in(argv[1], ifstream::in);
   string word;
   int suma = 0;
   map<char, int> alfabet;
   while (in >> word)
   {
      for (auto c : word)
      {
         c = tolower(c);
         if (c >= 'a' && c <= 'z')
         {
            alfabet[c]++;
            suma++;
         }
      }
   }
   for (auto el : alfabet)
   {
      cout << el.first << "-> " << static_cast<double>(el.second) / suma << endl;
   }
   in.close();
}