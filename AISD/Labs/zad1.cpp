#include <bits/stdc++.h>

#define ll long long int
#define sec second
#define fi first

using namespace std;

vector<pair<ll, ll>> sznurki;

bool cmp(pair<ll, ll> a, pair<ll, ll> b)
{
   if (a.fi == b.fi)
      return a.sec < b.sec;
   return a.fi < b.fi;
}

int main()
{
   ios_base::sync_with_stdio(false);

   int m;
   cin >> m;

   for (int i = 0; i < m; i++)
   {
      int d, n;
      cin >> d >> n;
      sznurki.push_back({d, n});
   }
   int result = 0;

   sort(sznurki.begin(), sznurki.end());

   int pointer = 0;

   while (pointer < m)
   {
      auto el = sznurki[pointer];
      int count = el.sec;
      if (count % 2 == 1)
      {
         result++;
         count--;
      }
      if (count == 0)
      {
         pointer++;
         continue;
      }
      ll target = el.fi * 2;
      count /= 2;
      sznurki[pointer].fi = target;
      sznurki[pointer].sec = count;
      auto it = lower_bound(sznurki.begin() + pointer + 1, sznurki.end(), make_pair(target, -1), cmp);
      if (it != sznurki.end() && (*it).fi == target)
      {
         int id = it - sznurki.begin();

         sznurki[id].sec += count;
         pointer++;
      }
   }
   cout << result << endl;
}