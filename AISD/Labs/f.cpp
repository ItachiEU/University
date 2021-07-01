#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 5;

int representative[maxn];
int ile[maxn];

int Find(int x)
{
   if (representative[x] == x)
      return representative[x];
   return representative[x] = Find(representative[x]);
}

void Union(int x, int y)
{
   x = Find(x);
   y = Find(y);

   if (x != y)
   {
      if (ile[x] < ile[y])
         swap(x, y);
      representative[y] = x;
      ile[x] += ile[y];
   }
}

struct edge
{
   int weight;
   int a;
   int b;
   edge(int w, int a, int b) : weight(w), a(a), b(b){};
};

bool cmp(edge a, edge b)
{
   if (a.weight == b.weight)
      return a.a < b.a;
   return a.weight > b.weight;
}

int main()
{
   ios_base::sync_with_stdio(false);

   vector<edge> edges;

   int n, m;
   cin >> n >> m;

   for (int i = 1; i <= n; i++)
   {
      representative[i] = i;
      ile[i] = 1;
   }

   for (int i = 0; i < m; i++)
   {
      int a, b, c;
      cin >> a >> b >> c;
      edges.push_back(edge(c, a, b));
   }
   sort(edges.begin(), edges.end(), cmp);

   int i = 0, result = edges[0].weight;
   while (ile[Find(1)] != n && i < edges.size())
   {
      edge e = edges[i];
      result = min(result, e.weight);
      Union(e.a, e.b);
      i++;
   }
   //cout << ile[Find(1)] << " " << n << endl;
   cout << result;
}