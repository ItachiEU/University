#include <bits/stdc++.h>
using namespace std;

/*
1. Identify all primary jump points by setting a directional flag in each node. [x]
2. Mark with distance all westward straight jump points and westward walls by sweeping the map left to right. [x]
3. Mark with distance all eastward straight jump points and eastward walls by sweeping the map right to left. [x]
4. Mark with distance all northward straight jump points and northward walls by sweeping the map up to down. [x]
5. Mark with distance all southward straight jump points and southward walls by sweeping the map down to up. [x]
6. Mark with distance all southwest/southeast diagonal jump points and southwest/southeast walls by sweeping the map down to up. [x]
7. Mark with distance all northwest/northeast diagonal jump points and northwest/northeast walls by sweeping the map up to down [x]
*/

enum dir
{
   NORTH = 0,
   NORTH_EAST = 1,
   EAST = 2,
   SOUTH_EAST = 3,
   SOUTH = 4,
   SOUTH_WEST = 5,
   WEST = 6,
   NORTH_WEST = 7
};

vector<string> board;
int node_distances[25][25][9];
bool jump_point[25][25][9];

void find_primary_jump_points(int height, int width)
{
   for (int i = 0; i < height; i++)
   {
      // EASTWARD
      for (int j = 0; j < width; j++)
      {
         if (board[i][j] == '#')
            continue;
         if (i - 1 >= 0 and board[i - 1][j] == '#' and j + 1 < width and board[i][j + 1] == '.' and board[i - 1][j + 1] == '.')
            jump_point[i][j + 1][EAST] = true;

         if (i + 1 < height and board[i + 1][j] == '#' and j + 1 < width and board[i][j + 1] == '.' and board[i + 1][j + 1] == '.')
            jump_point[i][j + 1][EAST] = true;
      }
      // WESTWARD
      for (int j = width - 1; j >= 0; j--)
      {
         if (board[i][j] == '#')
            continue;

         if (i - 1 >= 0 and board[i - 1][j] == '#' and j - 1 >= 0 and board[i][j - 1] == '.' and board[i - 1][j - 1] == '.')
            jump_point[i][j - 1][WEST] = true;

         if (i + 1 < height and board[i + 1][j] == '#' and j - 1 < width and board[i][j - 1] == '.' and board[i + 1][j - 1] == '.')
            jump_point[i][j - 1][WEST] = true;
      }
   }
   for (int j = 0; j < width; j++)
   {
      // SOUTHWARD
      for (int i = 0; i < height; i++)
      {
         if (board[i][j] == '#')
            continue;

         if (j - 1 >= 0 and board[i][j - 1] == '#' and i + 1 < height and board[i + 1][j] == '.' and board[i + 1][j - 1] == '.')
            jump_point[i + 1][j][SOUTH] = true;

         if (j + 1 < width and board[i][j + 1] == '#' and i + 1 < height and board[i + 1][j] == '.' and board[i + 1][j + 1] == '.')
            jump_point[i + 1][j][SOUTH] = true;
      }

      //NORTHWARD
      for (int i = height - 1; i >= 0; i--)
      {
         if (board[i][j] == '#')
            continue;

         if (j - 1 >= 0 and board[i][j - 1] == '#' and i - 1 >= 0 and board[i - 1][j] == '.' and board[i - 1][j - 1] == '.')
            jump_point[i - 1][j][NORTH] = true;

         if (j + 1 < width and board[i][j + 1] == '#' and i - 1 >= 0 and board[i - 1][j] == '.' and board[i - 1][j + 1] == '.')
            jump_point[i - 1][j][NORTH] = true;
      }
   }
}

void mark_straight_jump_points(int height, int width)
{
   //WESTWARD
   for (int i = 0; i < height; i++)
   {
      int count = -1;
      bool jumpPointLastSeen = false;
      for (int j = 0; j < width; j++)
      {
         if (board[i][j] == '#')
         {
            count = -1;
            jumpPointLastSeen = false;
            node_distances[i][j][WEST] = 0;
            continue;
         }
         count++;
         if (jumpPointLastSeen)
            node_distances[i][j][WEST] = count;
         else
            node_distances[i][j][WEST] = -count;

         if (jump_point[i][j][WEST])
         {
            count = 0;
            jumpPointLastSeen = true;
         }
      }
   }
   //EASTWARD
   for (int i = 0; i < height; i++)
   {
      int count = -1;
      bool jumpPointLastSeen = false;
      for (int j = width - 1; j >= 0; j--)
      {
         if (board[i][j] == '#')
         {
            count = -1;
            jumpPointLastSeen = false;
            node_distances[i][j][EAST] = 0;
            continue;
         }
         count++;
         if (jumpPointLastSeen)
            node_distances[i][j][EAST] = count;
         else
            node_distances[i][j][EAST] = -count;

         if (jump_point[i][j][EAST])
         {
            count = 0;
            jumpPointLastSeen = true;
         }
      }
   }
   //NORTHWARD
   for (int j = 0; j < width; j++)
   {
      int count = -1;
      bool jumpPointLastSeen = false;
      for (int i = 0; i < height; i++)
      {
         if (board[i][j] == '#')
         {
            count = -1;
            jumpPointLastSeen = false;
            node_distances[i][j][NORTH] = 0;
            continue;
         }
         count++;
         if (jumpPointLastSeen)
            node_distances[i][j][NORTH] = count;
         else
            node_distances[i][j][NORTH] = -count;

         if (jump_point[i][j][NORTH])
         {
            count = 0;
            jumpPointLastSeen = true;
         }
      }
   }
   //SOUTHWARD
   for (int j = 0; j < width; j++)
   {
      int count = -1;
      bool jumpPointLastSeen = false;
      for (int i = height - 1; i >= 0; i--)
      {
         if (board[i][j] == '#')
         {
            count = -1;
            jumpPointLastSeen = false;
            node_distances[i][j][SOUTH] = 0;
            continue;
         }
         count++;
         if (jumpPointLastSeen)
            node_distances[i][j][SOUTH] = count;
         else
            node_distances[i][j][SOUTH] = -count;

         if (jump_point[i][j][SOUTH])
         {
            count = 0;
            jumpPointLastSeen = true;
         }
      }
   }
}

void mark_diagonal_jump_points(int height, int width)
{

   for (int i = 0; i < height; ++i)
   {
      //NORTHWEST
      for (int j = 0; j < width; ++j)
      {
         if (board[i][j] == '#')
            continue;
         if (i == 0 or j == 0 or board[i - 1][j] == '#' or board[i][j - 1] == '#' or board[i - 1][j - 1] == '#')
            node_distances[i][j][NORTH_WEST] = 0; //Wall one away
         else if (board[i - 1][j] != '#' && board[i][j - 1] != '#' && (node_distances[i - 1][j - 1][NORTH] > 0 || node_distances[i - 1][j - 1][WEST] > 0))
            node_distances[i][j][NORTH_WEST] = 1; //Straight jump point one away
         else
         {
            //Increment from last
            int jumpDistance = node_distances[i - 1][j - 1][NORTH_WEST];
            if (jumpDistance > 0)
               node_distances[i][j][NORTH_WEST] = 1 + jumpDistance;
            else
               node_distances[i][j][NORTH_WEST] = -1 + jumpDistance;
         }
      }
      //NORTHEAST
      for (int j = width - 1; j >= 0; j--)
      {
         if (board[i][j] == '#')
            continue;

         if (i == 0 or j == width - 1 or board[i - 1][j] == '#' or board[i][j + 1] == '#' or board[i - 1][j + 1] == '#')
            node_distances[i][j][NORTH_EAST] = 0;
         else if (board[i - 1][j] != '#' and board[i][j + 1] != '#' and (node_distances[i - 1][j + 1][NORTH] > 0 or node_distances[i - 1][j + 1][EAST] > 0))
            node_distances[i][j][NORTH_EAST] = 1;
         else
         {
            int jumpDistance = node_distances[i - 1][j + 1][NORTH_EAST];

            if (jumpDistance > 0)
               node_distances[i][j][NORTH_EAST] = jumpDistance + 1;
            else
               node_distances[i][j][NORTH_EAST] = jumpDistance - 1;
         }
      }
   }
   for (int i = height - 1; i >= 0; i--)
   {
      // SOUTHEAST
      for (int j = width - 1; j >= 0; j--)
      {
         if (board[i][j] == '#')
            continue;

         if (i == height - 1 or j == width - 1 or board[i][j + 1] == '#' or board[i + 1][j + 1] == '#' or board[i + 1][j] == '#')
            node_distances[i][j][SOUTH_EAST] = 0;
         else if (node_distances[i + 1][j + 1][SOUTH] > 0 or node_distances[i + 1][j + 1][EAST] > 0)
            node_distances[i][j][SOUTH_EAST] = 1;
         else
         {
            int dist = node_distances[i + 1][j + 1][SOUTH_EAST];
            if (dist > 0)
               node_distances[i][j][SOUTH_EAST] = dist + 1;
            else
               node_distances[i][j][SOUTH_EAST] = dist - 1;
         }
      }
      // SOUTHWEST
      for (int j = 0; j < width; j++)
      {
         if (board[i][j] == '#')
            continue;

         if (i == height - 1 or j == 0 or board[i][j - 1] == '#' or board[i + 1][j - 1] == '#' or board[i + 1][j] == '#')
            node_distances[i][j][SOUTH_WEST] = 0;
         else if (node_distances[i + 1][j - 1][SOUTH] > 0 or node_distances[i + 1][j - 1][WEST] > 0)
            node_distances[i][j][SOUTH_WEST] = 1;
         else
         {
            int dist = node_distances[i + 1][j - 1][SOUTH_WEST];
            if (dist > 0)
               node_distances[i][j][SOUTH_WEST] = dist + 1;
            else
               node_distances[i][j][SOUTH_WEST] = dist - 1;
         }
      }
   }
}

int main()
{
   int height, width;
   cin >> width >> height;
   cin.ignore();
   for (int i = 0; i < height; i++)
   {
      string row; // A single row of the map consisting of passable terrain ('.') and walls ('#')
      cin >> row;
      board.push_back(row);
      cin.ignore();
   }

   find_primary_jump_points(height, width);
   mark_straight_jump_points(height, width);
   mark_diagonal_jump_points(height, width);

   for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++)
         if (board[i][j] == '.')
            cout << j << " " << i << " " << node_distances[i][j][NORTH] << " " << node_distances[i][j][NORTH_EAST] << " " << node_distances[i][j][EAST] << " " << node_distances[i][j][SOUTH_EAST] << " " << node_distances[i][j][SOUTH] << " " << node_distances[i][j][SOUTH_WEST] << " " << node_distances[i][j][WEST] << " " << node_distances[i][j][NORTH_WEST] << endl;
}