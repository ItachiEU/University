#include <bits/stdc++.h>
using namespace std;

struct Graph
{
private:
   unordered_map<string, int> nameToIndex;
   unordered_map<int, string> indexToName;

   int currNodeNumber;
   struct Node
   {
      string name;
      int number;
      Node(string n, int i) : name(n), number(i){};
   };
   struct Edge
   {
      Node target;
      int distance;
      Edge(Node n, int d) : target(n), distance(d){};
   };
   vector<vector<Edge>> graph;

public:
   vector<Edge> operator[](string name)
   {
      return graph[nameToIndex[name]];
   }
   vector<Edge> operator[](int number)
   {
      return graph[number];
   }
   Graph()
   {
      this->currNodeNumber = 0;
   }
   int addNode(string name) //return the index it assigned to that name
   {
      //Asuming that we are not adding duplicates
      //Otherwise store all nodes in a set/map
      nameToIndex[name] = currNodeNumber;
      indexToName[currNodeNumber] = name;

      graph.push_back({});

      currNodeNumber++;
      return currNodeNumber - 1;
   }
   void addEdge(int node1, int node2, int distance, bool undirected = false) // node1 -> node2 (distance) || node1 <-> node (distance)
   {
      Edge e1(Node(indexToName[node2], node2), distance);
      graph[node1].push_back(e1);
      if (undirected)
         addEdge(node2, node1, distance);
   }
   void addEdge(string snode1, string snode2, int distance, bool undirected = false) // node1 -> node2 (distance) || node1 <-> node (distance)
   {
      int node1 = nameToIndex[snode1], node2 = nameToIndex[snode2];
      Edge e1(Node(indexToName[node2], node2), distance);
      graph[node1].push_back(e1);
      if (undirected)
         addEdge(snode2, snode1, distance);
   }
   void removeNode(string name)
   {
      int index = nameToIndex[name];
      graph.erase(graph.begin() + index);
   }
   void removeNode(int index)
   {
      graph.erase(graph.begin() + index);
   }
   void removeEdge(int node1, int node2, bool bothWays = false)
   {
      auto removeIt = graph[node1].end();
      for (auto it = graph[node1].begin(); it != graph[node1].end(); it++)
      {
         if (it->target.number == node2)
         {
            removeIt = it;
            break;
         }
      }
      if (removeIt != graph[node1].end())
         graph[node1].erase(removeIt);
      if (bothWays)
         removeEdge(node2, node1);
   }
   void removeEdge(string snode1, string snode2, bool bothWays = false)
   {
      int node1 = nameToIndex[snode1];
      auto removeIt = graph[node1].end();
      for (auto it = graph[node1].begin(); it != graph[node1].end(); it++)
      {
         if (it->target.name == snode2)
         {
            removeIt = it;
            break;
         }
      }
      if (removeIt != graph[node1].end())
         graph[node1].erase(removeIt);
      if (bothWays)
         removeEdge(snode2, snode1);
   }
   void changeWeight(int node1, int node2, int newDistance)
   {
      for (auto it = graph[node1].begin(); it != graph[node1].end(); it++)
      {
         if (it->target.number == node2)
         {
            it->distance = newDistance;
            break;
         }
      }
      changeWeight(node2, node1, newDistance);
   }
   void changeWeight(string snode1, string snode2, int newDistance)
   {
      int node1 = nameToIndex[snode1];
      for (auto it = graph[node1].begin(); it != graph[node1].end(); it++)
      {
         if (it->target.name == snode2)
         {
            it->distance = newDistance;
            break;
         }
      }
      changeWeight(snode2, snode1, newDistance);
   }
   bool isPath(int node1, int node2)
   {
      queue<int> q;
      q.push(node1);
      unordered_set<int> seen;
      seen.insert(node1);
      while (!q.empty())
      {
         int v = q.front();
         //cout << "v -> " << v << endl;
         q.pop();
         if (v == node2)
            return true;

         for (int i = 0; i < (int)graph[v].size(); i++)
         {
            int neighbour = graph[v][i].target.number;
            //cout << "neighbour: " << neighbour << endl;
            if (!seen.count(neighbour))
            {
               q.push(neighbour);
               seen.insert(neighbour);
            }
         }
      }
      return false;
   }
   bool isPath(string node1, string node2)
   {
      return isPath(nameToIndex[node1], nameToIndex[node2]);
   }
};

int main()
{
   Graph graf;

   graf.addNode("zero");
   graf.addNode("jeden");
   graf.addNode("dwa");
   graf.addNode("trzy");
   graf.addNode("cztery");
   graf.addNode("pięć");

   graf.addEdge(1, 2, 3, true);
   graf.addEdge(0, 2, 5, true);
   graf.addEdge(2, 4, 2);
   graf.addEdge(0, 4, 1);
   graf.addEdge(1, 5, 7);
   graf.addEdge(4, 5, 0, true);

   cout << graf.isPath("cztery", "pięć") << endl;
   cout << graf.isPath(4, 5) << endl;
   cout << graf.isPath(4, 2) << endl;
   cout << graf.isPath(5, 0) << endl;
}