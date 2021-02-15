#include <bits/stdc++.h>
using namespace std;

int main()
{
   vector<double> input;
   istream_iterator<double> eos;
   istream_iterator<double> it(cin);
   while (it != eos)
   {
      input.push_back(*it);
      it++;
   }
   double sum = 0.0, variance = 0.0;
   for (auto val : input)
      sum += val;
   double mean = sum / input.size();
   for (auto val : input)
      variance += pow(val - mean, 2);
   variance /= input.size();
   double stdDev = sqrt(variance);
   cout << stdDev;
}