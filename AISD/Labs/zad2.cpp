#include <bits/stdc++.h>
using namespace std;
vector<int> input;

const int maxn = 2001, maxtarget = 1000001, INF = -1e9;

int dp[2][maxtarget];

int main()
{
   ios_base::sync_with_stdio(false);

   int n, total = 0;
   cin >> n;
   for (int i = 0; i < n; i++)
   {
      int a;
      cin >> a;
      input.push_back(a);
      total += a;
   }
   sort(input.begin(), input.end());
   for (int i = 0; i < total + 1; i++)
   {
      dp[1][i] = INF;
      dp[0][i] = INF;
   }

   dp[0][0] = 0;
   int lower = input[0], upper = input[0];
   for (int i = 1; i <= n; i++)
   {
      lower = max(0, min(lower, lower - input[i - 1]));
      upper = min(total, max(upper, upper + input[i - 1]));
      for (int j = lower; j <= upper; j++)
      {
         dp[i % 2][j] = j + input[i - 1] <= total ? max(dp[(i + 1) % 2][j], dp[(i + 1) % 2][j + input[i - 1]] + input[i - 1]) : dp[(i + 1) % 2][j];

         dp[i % 2][j] = max(max(dp[(i + 1) % 2][j], dp[i % 2][j]), dp[(i + 1) % 2][abs(j - input[i - 1])] + input[i - 1]);
      }
   }

   if (dp[n % 2][0] > 0)
   {
      cout << "TAK\n";
      cout << dp[n % 2][0] / 2;
   }
   else
   {
      cout << "NIE\n";
      for (int i = 1; i <= total; i++)
      {
         if (dp[n % 2][i] > 0 && dp[n % 2][i] != i)
         {
            cout << i;
            return 0;
         }
      }
   }
}