#include <bits/stdc++.h>

using namespace std;

vector<int> topSort(int n, vector<pair<int, int>> edges)
{
   // returns {-1} if impossible

   vector<int> inDegree(n + 1, 0);
   vector<int> G[n + 1];
   vector<int> result;
   priority_queue<int> q;

   //preprocessing
   for (auto edge : edges)
   {
      inDegree[edge.second]++;
      G[edge.first].push_back(edge.second);
   }

   for (int i = 1; i <= n; i++)
      if (inDegree[i] == 0)
         q.push(-i);

   //algorytm
   while (!q.empty())
   {
      int v = -q.top();
      result.push_back(v);
      q.pop();
      for (int i = 0; i < G[v].size(); i++)
      {
         inDegree[G[v][i]]--;
         if (inDegree[G[v][i]] == 0)
            q.push(-G[v][i]);
      }
   }

   if (result.size() != n)
      return {-1};

   return result;
}

int main()
{
}