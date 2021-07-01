#include <bits/stdc++.h>

using namespace std;
const int maxn = 5005;
const int c = (1 << 5);
vector<int> forbidden;
int prep[c][c][c];
int dp[c][c][2];

void readPatterns(int p)
{
   for (int i = 0; i < p; i++)
   {
      int pattern = 0, mult = 1;
      for (int j = 0; j < 9; j++)
      {
         char a;
         cin >> a;
         if (a == 'x')
            pattern += mult;
         mult = (mult << 1);
      }
      forbidden.push_back(pattern);
   }
}

bool collisionDetected(int col1, int col2, int col3)
{
   for (int j = 0; j < 3; j++)
   {
      int temp = 0, mult = 1;
      for (int i = 0; i < 3; i++)
      {
         if ((col1 & (1 << i)))
            temp += mult;
         mult = (mult << 1);
         if ((col2 & (1 << i)))
            temp += mult;
         mult = (mult << 1);
         if ((col3 & (1 << i)))
            temp += mult;
         mult = (mult << 1);
      }
      for (auto pattern : forbidden)
      {
         if (temp == pattern) // pattern in block
            return true;
      }
      col1 = col1 >> 1;
      col2 = col2 >> 1;
      col3 = col3 >> 1;
   }
   return false;
}

int main()
{
   ios_base::sync_with_stdio(false);
   int n, p, mod;
   cin >> n >> p >> mod;

   readPatterns(p);

   // preprocessing
   int start = 0;
   for (int i = 0; i < c; i++)
   { //first column
      for (int j = 0; j < c; j++)
      { // second column
         dp[i][j][0] = 1;
         for (int k = 0; k < c; k++)
         { //column we are adding
            if (!collisionDetected(i, j, k))
            {
               prep[i][j][k] = 1;
            }
            else
               prep[i][j][k] = 0;
         }
      }
   }
   for (int x = 3; x <= n; x++)
   {
      for (int i = 0; i < c; i++)
      {
         for (int j = 0; j < c; j++)
         {
            dp[i][j][x % 2] = 0;
         }
      }
      for (int i = 0; i < c; i++)
      {
         for (int j = 0; j < c; j++)
         {
            for (int k = 0; k < c; k++)
            {
               if (prep[i][j][k])
               {
                  dp[j][k][x % 2] += dp[i][j][(x + 1) % 2];
                  dp[j][k][x % 2] %= mod;
               }
            }
         }
      }
   }
   int result = 0;
   for (int i = 0; i < c; i++)
      for (int j = 0; j < c; j++)
      {
         result += dp[i][j][n % 2];
         result %= mod;
      }
   cout << result << endl;
}