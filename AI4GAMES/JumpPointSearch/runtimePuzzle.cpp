#include <bits/stdc++.h>
using namespace std;
enum dir
{
   NORTH = 0,
   NORTH_EAST = 1,
   EAST = 2,
   SOUTH_EAST = 3,
   SOUTH = 4,
   SOUTH_WEST = 5,
   WEST = 6,
   NORTH_WEST = 7,
   UNDEFINED = 8
};

vector<bool> cardinal = {true, false, true, false, true, false, true, false, false};
vector<bool> diagonal = {false, true, false, true, false, true, false, true, false};

int node_distances[25][25][9];
unordered_map<int, vector<int>> validDirections = {
    {SOUTH, {WEST, SOUTH_WEST, SOUTH, SOUTH_EAST, EAST}},
    {SOUTH_EAST, {SOUTH, SOUTH_EAST, EAST}},
    {EAST, {SOUTH, SOUTH_EAST, EAST, NORTH_EAST, NORTH}},
    {NORTH_EAST, {EAST, NORTH_EAST, NORTH}},
    {NORTH, {EAST, NORTH_EAST, NORTH, NORTH_WEST, WEST}},
    {NORTH_WEST, {NORTH, NORTH_WEST, WEST}},
    {WEST, {NORTH, NORTH_WEST, WEST, SOUTH_WEST, SOUTH}},
    {SOUTH_WEST, {WEST, SOUTH_WEST, SOUTH}},
    {UNDEFINED, {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST}}};

class Node
{
public:
   int dir;
   int row;
   int column;
   double cost;
   double givenCost;
   Node *parent;
   Node(int d, int r, int col, double cos, Node *p) : dir(d), row(r), column(col), cost(cos), givenCost(cos), parent(p)
   {
   }
   Node()
   {
      row = -1;
      column = -1;
      parent = NULL;
      cost = 0.0;
      givenCost = 0.0;
      dir = UNDEFINED;
   }
};

bool printedNodes[25][25];

bool cmp(Node *a, Node *b)
{
   return a->cost < b->cost;
}
struct CompareNodes
{
   bool operator()(Node *a, Node *b)
   {
      return a->cost > b->cost;
   }
};

bool isSameCardinalDirection(Node *t, int dir, int goal_row, int goal_column)
{
   switch (dir)
   {
   case NORTH:
      if (goal_column == t->column and goal_row < t->row)
         return true;
      break;
   case SOUTH:
      if (goal_column == t->column and goal_row > t->row)
         return true;
      break;
   case WEST:
      if (goal_column < t->column and goal_row == t->row)
         return true;
      break;
   case EAST:
      if (goal_column > t->column and goal_row == t->row)
         return true;
      break;
   }
   return false;
}

bool isSameGeneralDirection(Node *t, int dir, int goal_row, int goal_column)
{
   switch (dir)
   {
   case NORTH_EAST:
      if (goal_column >= t->column and goal_row <= t->row)
         return true;
      break;
   case NORTH_WEST:
      if (goal_column <= t->column and goal_row <= t->row)
         return true;
      break;
   case SOUTH_EAST:
      if (goal_column >= t->column and goal_row >= t->row)
         return true;
      break;
   case SOUTH_WEST:
      if (goal_column <= t->column and goal_row >= t->row)
         return true;
      break;
   }
   return false;
}

int diffNodes(Node *t, int goal_row, int goal_column)
{
   return abs(t->row - goal_row) + abs(t->column - goal_column);
}

int diffNodesRow(Node *t, int goal_row)
{
   return abs(t->row - goal_row);
}

int diffNodesColumn(Node *t, int goal_column)
{
   return abs(t->column - goal_column);
}
pair<int, int> getNewCoordinatesDiagonal(Node *curNode, int dir, int minDiff)
{
   switch (dir)
   {
   case NORTH_EAST:
      return {curNode->row - minDiff, curNode->column + minDiff};
   case NORTH_WEST:
      return {curNode->row - minDiff, curNode->column - minDiff};
   case SOUTH_EAST:
      return {curNode->row + minDiff, curNode->column + minDiff};
   case SOUTH_WEST:
      return {curNode->row + minDiff, curNode->column - minDiff};
   }
}
pair<int, int> getNewCoordinates(Node *curNode, int dir, int dist)
{
   switch (dir)
   {
   case NORTH_EAST:
      return {curNode->row - dist, curNode->column + dist};
   case NORTH_WEST:
      return {curNode->row - dist, curNode->column - dist};
   case SOUTH_EAST:
      return {curNode->row + dist, curNode->column + dist};
   case SOUTH_WEST:
      return {curNode->row + dist, curNode->column - dist};
   case NORTH:
      return {curNode->row - dist, curNode->column};
   case SOUTH:
      return {curNode->row + dist, curNode->column};
   case WEST:
      return {curNode->row, curNode->column - dist};
   case EAST:
      return {curNode->row, curNode->column + dist};
   }
}
double SQRT2 = 1.414213562;

double CalculateHeuristic(Node *t, int goal_row, int goal_column)
{
   return SQRT2 * min(abs(t->row - goal_row), abs(t->column - goal_column)) + abs(abs(t->row - goal_row) - abs(t->column - goal_column));
}

double onOpenList[25][25];
bool onClosedList[25][25];

/**
 * Compute the nodes visited by the JPS+ algorithm when performing runtime phase search.
 **/

int main()
{
   int width;  // Width of the map
   int height; // Height of the map
   cin >> width >> height;
   cin.ignore();
   int start_column; // coordinate of the starting tile
   int start_row;    // coordinate of the starting tile
   int goal_column;  // coordinate of the goal tile
   int goal_row;     // coordinate of the goal tile
   cin >> start_column >> start_row >> goal_column >> goal_row;
   cin.ignore();
   int open; // number of open tiles on the map
   cin >> open;
   //cerr << open << endl;
   cin.ignore();
   for (int i = 0; i < open; i++)
   {
      int row, column, n, ne, e, se, s, sw, w, nw;
      cin >> column >> row >> n >> ne >> e >> se >> s >> sw >> w >> nw;
      //cerr << column << " " << row << " " << n << " " << ne << " " << e << " " << se << " " << s << " " << sw << " " << w << " " << nw << endl;
      cin.ignore();
      node_distances[row][column][NORTH] = n;
      node_distances[row][column][NORTH_EAST] = ne;
      node_distances[row][column][EAST] = e;
      node_distances[row][column][SOUTH_EAST] = se;
      node_distances[row][column][SOUTH] = s;
      node_distances[row][column][SOUTH_WEST] = sw;
      node_distances[row][column][WEST] = w;
      node_distances[row][column][NORTH_WEST] = nw;
   }
   bool pathFound = false;
   priority_queue<Node *, vector<Node *>, CompareNodes> q;
   Node *p = new Node(); // initial parent pointer
   Node *start = new Node(NULL, start_row, start_column, 0.0, p);
   q.push(start); // Initialize the queue
   onOpenList[start_row][start_row] = 0.00000001;
   // game loop
   while (!q.empty())
   {
      Node *curNode = q.top();
      if (!onClosedList[curNode->row][curNode->column])
         cout << curNode->column << " " << curNode->row << " " << curNode->parent->column << " " << curNode->parent->row << " " << curNode->givenCost << endl;
      onOpenList[curNode->row][curNode->column] = 0.0;
      onClosedList[curNode->row][curNode->column] = true;
      Node *parent = curNode->parent;
      q.pop();
      if (curNode->row == goal_row and curNode->column == goal_column)
      {
         pathFound = true;
         return 0;
      }
      for (auto dir : validDirections[parent->dir])
      {
         Node *newSuccessor = NULL;
         double givenCost;
         if (
             cardinal[dir] and
             isSameCardinalDirection(curNode, dir, goal_row, goal_column) and
             diffNodes(curNode, goal_row, goal_column) <= abs(node_distances[curNode->row][curNode->column][dir]))
         {
            newSuccessor = new Node();
            newSuccessor->row = goal_row;
            newSuccessor->column = goal_column;
            givenCost = curNode->givenCost + diffNodes(curNode, goal_row, goal_column);
            newSuccessor->givenCost = givenCost;
            newSuccessor->parent = new Node(dir, curNode->row, curNode->column, curNode->givenCost, curNode->parent);
         }
         else if (
             diagonal[dir] and
             min(diffNodesRow(curNode, goal_row),
                 diffNodesColumn(curNode, goal_column)) > 0 and
             isSameGeneralDirection(curNode, dir, goal_row, goal_column) and
             (diffNodesRow(curNode, goal_row) <=
                  abs(node_distances[curNode->row][curNode->column][dir]) ||
              (diffNodesColumn(curNode, goal_column) <=
               abs(node_distances[curNode->row][curNode->column][dir]))))
         {

            int minDiff = min(diffNodesRow(curNode, goal_row),
                              diffNodesColumn(curNode, goal_column));
            auto cords = getNewCoordinatesDiagonal(curNode, dir, minDiff);
            newSuccessor = new Node(dir, cords.first, cords.second, 0.0, curNode);
            givenCost = curNode->givenCost + (SQRT2 * minDiff);
            newSuccessor->givenCost = givenCost;
            newSuccessor->parent = new Node(dir, curNode->row, curNode->column, curNode->givenCost, curNode->parent);
         }
         else if (node_distances[curNode->row][curNode->column][dir] > 0)
         {
            auto cords = getNewCoordinates(curNode, dir, node_distances[curNode->row][curNode->column][dir]);
            newSuccessor = new Node(dir, cords.first, cords.second, 0.0, curNode);
            givenCost = diffNodes(curNode, newSuccessor->row, newSuccessor->column);
            if (diagonal[dir])
               givenCost *= SQRT2 / 2.0;
            givenCost += curNode->givenCost;
            newSuccessor->givenCost = givenCost;
            newSuccessor->parent = new Node(dir, curNode->row, curNode->column, curNode->givenCost, curNode->parent);
         }
         // A*
         if (newSuccessor != NULL)
         {
            if (onOpenList[newSuccessor->row][newSuccessor->column] == 0.0 and !onClosedList[newSuccessor->row][newSuccessor->column])
            {
               newSuccessor->cost = newSuccessor->givenCost + CalculateHeuristic(newSuccessor, goal_row, goal_column);
               q.push(newSuccessor);
               onOpenList[newSuccessor->row][newSuccessor->column] = newSuccessor->givenCost;
            }
            else if (newSuccessor->givenCost < onOpenList[newSuccessor->row][newSuccessor->column])
            {
               newSuccessor->cost = newSuccessor->givenCost + CalculateHeuristic(newSuccessor, goal_row, goal_column);
               onOpenList[newSuccessor->row][newSuccessor->column] = newSuccessor->givenCost;
               q.push(newSuccessor);
            }
         }
      }
   }

   cout << "NO PATH" << endl;
}