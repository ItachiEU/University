#include <bits/stdc++.h>
using namespace std;

int phi(int target)
{
   int result = 0;
   for (int i = 1; i <= target; i++)
      if (__gcd(target, i) == 1)
         result++;
   return result;
}

int main()
{
   int k;
   cin >> k;

   vector<int> calculatedPhi;
   for (int i = 1; i <= k; i++)
      calculatedPhi.push_back(phi(i));

   ofstream out("phi.txt");
   ostream_iterator<int> it(out, "; ");
   for (auto val : calculatedPhi)
   {
      *it = val;
      it++;
   }
}