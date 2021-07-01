#include <bits/stdc++.h>

using namespace std;

int partition(vector<int> &input, int left, int right)
{
   int pivot = input[right];
   int pIndex = left;

   for (int i = left; i < right; i++)
   {
      if (input[i] <= pivot)
      {

         if (pIndex != i)
         {
            swap(input[i], input[pIndex]);
         }
         pIndex++;
      }
   }
   if (pIndex != right)
   {
      swap(input[pIndex], input[right]);
   }
   cout << "Pivot: " << pivot << endl;
   for (int i = 0; i < input.size(); i++)
      cout << input[i] << " ";
   cout << endl;
   return pIndex;
}

int main()
{
   ios_base::sync_with_stdio(false);

   vector<int> input;
   int n;
   cin >> n;

   for (int i = 1; i <= n; i++)
      input.push_back(i);

   random_shuffle(input.begin(), input.end());

   for (int i = 0; i < n; i++)
      cout
          << input[i] << " ";
   cout << endl;

   int i = 0,
       j = n - 1;
   while (i < n)
   {
      if (j > i)
      {
         cout << "Przedział: " << i << " " << j << endl;
         int p = partition(input, i, j);
         int m = -1, ind = -1;
         for (int k = p + 1; k <= j; k++)
         {
            if (input[k] > m)
            {
               m = input[k];
               ind = k;
            }
         }
         if (ind != -1)
            swap(input[p], input[ind]);
         j = p - 1;
      }
      else
      {
         i = i + 1;
         for (int k = i; k < n; k++)
         {
            if (input[k] > input[i])
            {
               j = k - 1;
               break;
            }
            else if (k == n - 1 && input[k] < input[i])
            {
               j = k;
            }
         }
      }
   }
   for (auto el : input)
      cout << el << " ";
   cout << endl;
}