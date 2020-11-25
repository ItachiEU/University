#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 mt(rd());

string generateWord(int length, vector<double> &frequencies)
{
   vector<int> frequenciesInt;
   for (auto el : frequencies)
      frequenciesInt.push_back(static_cast<int>(el * 100));

   string result;
   discrete_distribution<int> distribution(frequenciesInt.begin(), frequenciesInt.end());
   for (int i = 0; i < length; i++)
   {
      char t = static_cast<char>(distribution(mt) + 97);
      result += t;
   }
   cout << result << endl;
   return result;
}

int main(int argc, char **argv)
{
   vector<double> frequencies = {8.12, 1.49, 2.71, 4.32, 12.02, 2.30, 2.03, 5.92, 7.31, 0.10, 0.69, 3.98, 2.61, 6.95, 7.68, 1.82, 0.11, 6.02, 6.28, 9.10, 2.88, 1.11, 2.09, 0.17, 2.11, 0.07};

   string name = argv[1];
   binomial_distribution<int> binom(11, 0.5);
   ofstream out(name);
   istringstream iss(argv[2]);
   int length;
   iss >> length;
   for (int i = 0; i < length; i++)
   {
      int wordLength = binom(mt) + 1;
      out << generateWord(wordLength, frequencies);
      if (i != length - 1)
         out << " ";
   }
}