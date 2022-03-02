#include <bits/stdc++.h>
#define assertm(exp, msg) assert(((void)msg, exp))
using namespace std;

int MAP[13][17];

vector<pair<int, int>> move_shift = {{-1, 0}, {0, 1}, {1, 0}, {-1, 0}};
unordered_set<int> obstacles = {1, 7, 8, 9, 10};
int scorePerEntity[12] = {100, 0, 100, 0, 0, 0, 0, 1, 6, 14, 8, 10};
int dmgWeapon[4] = {10, 6, 7, 8};
int viewRange[12] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 3};
int attackRange[12] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1};
int dmgPerEntity[12] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 3};

enum direction
{
   UP = 0,
   RIGHT = 1,
   DOWN = 2,
   LEFT = 3
};

enum weapon
{
   SWORD = 0,
   HAMMER = 1,
   SCYTHE = 2,
   BOW = 3
};

enum entity_type
{
   UNKNOWN = -1,
   EXIT = 0,
   OBSTACLE = 1,
   TREASURE = 2,
   POTION = 3,
   HAMMER_CHARGE = 4,
   SCYTHE_CHARGE = 5,
   BOW_CHARGE = 6,
   BOX = 7,
   SKELETON = 8,
   GARGOYLE = 9,
   ORC = 10,
   VAMPIRE = 11,
};

class Entity
{
public:
   int HP;
   int x;
   int y;
   int type;
   int value;
   Entity()
   {
      this->HP = -1;
      this->x = -1;
      this->y = -1;
      this->type = -1;
      this->value = -1;
   }
   Entity(int type, int value, int x, int y, int hp)
   {
      this->HP = hp;
      this->type = type;
      this->value = value;
      this->x = x;
      this->y = y;
   }
};

class Move
{
public:
   char type; // 'a' - attack, 'm' - move
   int x;
   int y;
   int weapon;
   Move(char t, int x, int y, int weapon = -1)
   {
      this->type = t;
      this->x = x;
      this->y = y;
      this->weapon = weapon;
   };
   Move()
   {
      this->type = 'o';
      this->x = -1;
      this->y = -1;
      this->weapon = -1;
   }
   ~Move()
   {
   }
   void print(bool debug = false)
   {
      string msg = this->type == 'a' ? "ATTACK " + to_string(weapon) : "MOVE";
      msg += " " + to_string(this->x) + " " + to_string(this->y);
      if (debug)
         cerr << msg << endl;
      else
         cout << msg << endl;
   }
};

bool isCardinalMove(int current_x, int current_y, int new_x, int new_y)
{
   if (abs(current_x - new_x) + abs(current_y - new_y) <= 1) // not equal to include staying in place as well
      return true;
   return false;
}

vector<pair<int, int>> getCardinalHammerTiles(int start_x, int start_y, int target_x, int target_y)
{
   vector<pair<int, int>> result;
   if (start_x == target_x)
   {
      for (int i = max(start_x - 1, 0); i <= min(start_x + 1, 15); i++)
         result.push_back({i, target_y});
   }
   else if (start_y == target_y)
   {
      for (int i = max(start_y - 1, 0); i <= min(start_y + 1, 11); i++)
         result.push_back({target_x, i});
   }
   return result;
}
vector<pair<int, int>> getDiagonalHammerTiles(int start_x, int start_y, int target_x, int target_y)
{
   int x_diff = target_x - start_x;
   int y_diff = target_y - start_y;
   return {{target_x, target_y}, {start_x + x_diff, start_y}, {start_x, start_y + y_diff}};
}

vector<pair<int, int>> getCardinalScytheTiles(int start_x, int start_y, int target_x, int target_y)
{
   vector<pair<int, int>> result;
   if (start_x == target_x)
   {
      for (int i = max(min(start_y, target_y), 0); i <= min(max(start_y, target_y), 11); i++)
         result.push_back({start_x, i});
   }
   else if (start_y == target_y)
   {
      for (int i = max(min(start_x, target_x), 0); i <= min(max(start_x, target_x), 15); i++)
         result.push_back({i, start_y});
   }
   return result;
}
vector<pair<int, int>> getDiagonalScytheTiles(int start_x, int start_y, int target_x, int target_y)
{
   int x_diff = target_x - start_x;
   int y_diff = target_y - start_y;
   if (abs(x_diff) > 1 and abs(y_diff) > 1)
      return {{target_x, target_y}, {start_x + x_diff / 2, start_y + y_diff / 2}};
   return {{target_x, target_y}};
}
int getDistance(pair<int, int> a, pair<int, int> b)
{
   if (a.first == b.first or a.second == b.second)
      return abs(a.first - b.first) + abs(a.second - b.second);
   if (abs(a.first - b.first) == abs(a.second - b.second))
      return abs(a.first - b.first);
   return 10; // not a queen move
}

int getViewDistance(pair<int, int> a, pair<int, int> b)
{
   return max(abs(a.first - b.first), abs(a.second - b.second));
}

class State
{
public:
   vector<vector<pair<Entity, Entity>>> entity_info; // {Entity, Entity} -> {Monster if present, Other stufff if present}
   vector<pair<int, int>> monsters;
   map<pair<int, int>, bool> treasure;
   set<pair<int, int>> visited;
   int player_HP;
   vector<int> charges;
   int score;
   int player_x;
   int player_y;
   bool on_exit;
   int turn;
   State(State *s)
   {
      this->entity_info = s->entity_info;
      this->monsters = s->monsters;
      this->player_HP = s->player_HP;
      this->charges = s->charges;
      this->score = s->score;
      this->player_x = s->player_x;
      this->player_y = s->player_y;
      this->on_exit = s->on_exit;
      this->visited = s->visited;
      this->turn = s->turn;
      this->treasure = s->treasure;
   }
   State(int hp, int x, int y, int score, vector<int> charges, vector<pair<int, int>> monsters, vector<vector<pair<Entity, Entity>>> info, map<pair<int, int>, bool> treasure)
   {
      this->entity_info = info;
      this->monsters = monsters;
      this->player_HP = hp;
      this->charges = charges;
      this->score = score;
      this->player_x = x;
      this->player_y = y;
      this->on_exit = false;
      this->visited = {};
      this->turn = 0;
      this->treasure = treasure;
   }
   int applyPlayerMove(Move move)
   {
      this->turn++;
      int dmgDealt = 0;
      if (move.type == 'm')
      {
         this->player_x = move.x;
         this->player_y = move.y;
         this->visited.insert({move.x, move.y});
         if (this->entity_info[move.y][move.x].second.type != -1) // handle pick up
         {
            this->score += scorePerEntity[this->entity_info[move.y][move.x].second.type]; // add score
            switch (this->entity_info[move.y][move.x].second.type)
            {
            case EXIT:
               this->on_exit = true;
               break;
            case TREASURE:
               if (this->treasure.count({move.y, move.x}))
                  this->treasure.erase({move.y, move.x});
               break;
            case POTION:
               this->player_HP = min(20, this->player_HP + 10);
               break;
            case HAMMER_CHARGE:
               this->charges[HAMMER]++;
               break;
            case SCYTHE_CHARGE:
               this->charges[SCYTHE_CHARGE]++;
               break;
            case BOW_CHARGE:
               this->charges[BOW_CHARGE]++;
               break;
            }
            this->entity_info[move.y][move.x].second = Entity(); // clear after pick up
         }
      }
      if (move.type == 'a')
      {
         vector<pair<int, int>> tiles;
         switch (move.weapon)
         {
         case SWORD:
            if (this->entity_info[move.y][move.x].first.type != -1) // if monster is present
            {
               dmgDealt += min(this->entity_info[move.y][move.x].first.HP, dmgWeapon[SWORD]);
               this->entity_info[move.y][move.x].first.HP -= dmgWeapon[SWORD];
               if (this->entity_info[move.y][move.x].first.HP <= 0) // handle monster death
               {
                  this->score += scorePerEntity[this->entity_info[move.y][move.x].first.type];
                  this->removeMonster(move.x, move.y);
                  this->entity_info[move.y][move.x].first = Entity();
               }
            }
            break;
         case HAMMER:
            if (isCardinalMove(this->player_x, this->player_y, move.x, move.y))
               tiles = getCardinalHammerTiles(this->player_x, this->player_y, move.x, move.y);
            else
               tiles = getDiagonalHammerTiles(this->player_x, this->player_y, move.x, move.y);

            this->charges[HAMMER]--;
            for (auto tile : tiles)
            {
               if (this->entity_info[tile.second][tile.first].first.type != -1) // if monster is present
               {
                  dmgDealt += min(this->entity_info[move.y][move.x].first.HP, dmgWeapon[HAMMER]);
                  this->entity_info[tile.second][tile.first].first.HP -= dmgWeapon[HAMMER];
                  if (this->entity_info[tile.second][tile.first].first.HP <= 0) // handle monster death
                  {
                     this->score += scorePerEntity[this->entity_info[tile.second][tile.first].first.type];
                     this->removeMonster(tile.first, tile.second);
                     this->entity_info[tile.second][tile.first].first = Entity();
                  }
               }
            }
            break;
         case SCYTHE:
            if (isCardinalMove(this->player_x, this->player_y, move.x, move.y))
               tiles = getCardinalScytheTiles(this->player_x, this->player_y, move.x, move.y);
            else
               tiles = getDiagonalScytheTiles(this->player_x, this->player_y, move.x, move.y);

            this->charges[SCYTHE]--;
            for (auto tile : tiles)
            {
               if (this->entity_info[tile.second][tile.first].first.type != -1) // if monster is present
               {
                  dmgDealt += min(this->entity_info[move.y][move.x].first.HP, dmgWeapon[SCYTHE]);
                  this->entity_info[tile.second][tile.first].first.HP -= dmgWeapon[SCYTHE];
                  if (this->entity_info[tile.second][tile.first].first.HP <= 0) // handle monster death
                  {
                     this->score += scorePerEntity[this->entity_info[tile.second][tile.first].first.type];
                     this->removeMonster(tile.first, tile.second);
                     this->entity_info[tile.second][tile.first].first = Entity();
                  }
               }
            }
            break;
         case BOW:
            this->charges[BOW]--;
            if (this->entity_info[move.y][move.x].first.type != -1) // if monster is present
            {
               dmgDealt += min(this->entity_info[move.y][move.x].first.HP, dmgWeapon[BOW]);
               this->entity_info[move.y][move.x].first.HP -= dmgWeapon[BOW];
               if (this->entity_info[move.y][move.x].first.HP <= 0) // handle monster death
               {
                  this->score += scorePerEntity[this->entity_info[move.y][move.x].first.type];
                  this->removeMonster(move.x, move.y);
                  this->entity_info[move.y][move.x].first = Entity();
               }
            }
            break;
         }
      }
      return dmgDealt;
   }
   void removeMonster(int x, int y)
   {
      for (int i = 0; i < this->monsters.size(); i++)
         if (this->monsters[i].first == x and this->monsters[i].second == y)
         {
            this->monsters.erase(this->monsters.begin() + i);
            break;
         }
   }
   pair<int, int> getMonsterMove(int start_x, int start_y)
   {
      queue<pair<int, int>> q;
      int visited[13][16];
      pair<int, int> parents[13][16];
      bool found = false;
      memset(visited, 0, sizeof(int) * 13 * 16);
      q.push({start_x, start_y});
      parents[start_y][start_x] = {-1, -1};
      visited[start_y][start_x] = 1;
      while (!q.empty())
      {
         auto t = q.front();
         if (t.first == this->player_x and t.second == this->player_y)
         {
            found = true;
            break;
         }
         q.pop();
         for (int i = 0; i < move_shift.size(); i++)
         {
            pair<int, int> new_tile = {t.first + move_shift[i].first, t.second + move_shift[i].second};
            if (new_tile.first < 0 or new_tile.first > 15 or new_tile.second < 0 or new_tile.second > 11)
               continue;
            if (!visited[new_tile.second][new_tile.first] and this->entity_info[new_tile.second][new_tile.first].first.type == -1 and this->entity_info[new_tile.second][new_tile.first].second.type != 1 and MAP[new_tile.second][new_tile.first] != UNKNOWN and MAP[new_tile.second][new_tile.first] != OBSTACLE)
            {
               visited[new_tile.second][new_tile.first] = 1;
               q.push(new_tile);
               parents[new_tile.second][new_tile.first] = t;
            }
         }
      }
      if (!found)
      {
         for (int i = 0; i < move_shift.size(); i++)
         {
            pair<int, int> new_tile = {start_x + move_shift[i].first, start_y + move_shift[i].second};
            if (new_tile.first < 0 or new_tile.first > 15 or new_tile.second < 0 or new_tile.second > 11)
               continue;
            if (abs(new_tile.first - this->player_x) + abs(new_tile.second - this->player_y) < abs(start_x - this->player_x) + abs(start_y - this->player_y) and this->entity_info[new_tile.second][new_tile.first].first.type == -1 and this->entity_info[new_tile.second][new_tile.first].second.type != 1 and MAP[new_tile.second][new_tile.first] != UNKNOWN and MAP[new_tile.second][new_tile.first] != OBSTACLE) // if it gets monster closer
               return new_tile;
         }
         return {-1, -1};
      }
      // Reconstruct the path
      pair<int, int> ending = {this->player_x, this->player_y};
      list<pair<int, int>> path;
      while (parents[ending.second][ending.first] != make_pair(-1, -1))
      {
         path.push_back(ending);
         ending = parents[ending.second][ending.first];
      }
      return path.back();
   }

   void simulateMonstersMove()
   {
      if (this->on_exit)
         return;

      for (int i = 0; i < this->monsters.size(); i++)
      {
         pair<int, int> cords = this->monsters[i];
         int dist = getViewDistance({this->player_x, this->player_y}, cords);
         if (this->entity_info[cords.second][cords.first].first.type == -1)
            continue;

         if (dist > viewRange[this->entity_info[cords.second][cords.first].first.type]) // if player invisible to them, stay in place
            continue;
         if (dist <= attackRange[this->entity_info[cords.second][cords.first].first.type]) // if can attack, attack
         {
            this->player_HP -= dmgPerEntity[this->entity_info[cords.second][cords.first].first.type];
            this->score -= dmgPerEntity[this->entity_info[cords.second][cords.first].first.type];
            if (this->player_HP <= 0)
               this->score -= 10000;
         }
         else if (dist <= viewRange[this->entity_info[cords.second][cords.first].first.type]) // move towards player if you can see him
         {
            // TO DO:finish up
            pair<int, int> monster_move = getMonsterMove(cords.first, cords.second);
            if (monster_move != make_pair(-1, -1))
            {
               assertm(this->entity_info[monster_move.second][monster_move.first].first.type == -1, "Check if monster destination is empty");
               this->entity_info[monster_move.second][monster_move.first].first = this->entity_info[cords.second][cords.first].first; // move entity to new position
               this->entity_info[cords.second][cords.first].first = Entity();                                                         // set old location to null
               this->monsters[i] = monster_move;                                                                                      // update monsters array
            }
         }
      }
   }
};

int evaluateState(State *game, State *gameCopy)
{
   int result = gameCopy->score;
   result += 10 * (gameCopy->visited.size() - gameCopy->turn); // penalize not exploring the map
   return result;
}

vector<pair<int, int>> getTilesInSight(int player_x, int player_y)
{
   vector<pair<int, int>> tiles;
   for (int y = max(player_y - 3, 0); y <= min(player_y + 3, 11); y++)
      for (int x = max(player_x - 3, 0); x <= min(player_x + 3, 15); x++)
      {
         if (y == player_y and x == player_x)
            continue;
         if (MAP[y][x] != UNKNOWN and MAP[y][x] != OBSTACLE)
            tiles.push_back({x, y});
      }
   return tiles;
}

void simulateMove(State *startState, Move move)
{
   // PLAYER MOVE
   startState->applyPlayerMove(move);
   // MONSTERS MOVE
   startState->simulateMonstersMove();
}

vector<Move> getPossibleMoves(State *s)
{
   vector<pair<int, int>> tilesToConsider = getTilesInSight(s->player_x, s->player_y);
   vector<Move> resultMoves;
   for (auto tile : tilesToConsider) // tile = (x, y)
   {
      if (s->entity_info[tile.second][tile.first].first.type == -1 and s->entity_info[tile.second][tile.first].second.type != 1 and isCardinalMove(s->player_x, s->player_y, tile.first, tile.second)) // cardinal move without obstacle
      {
         Move m('m', tile.first, tile.second);
         resultMoves.push_back(m);
      }
      if (s->entity_info[tile.second][tile.first].first.type != -1) // consider attacking monster or a box
      {
         int dist = getDistance(tile, {s->player_x, s->player_y});
         if (getViewDistance(tile, {s->player_x, s->player_y}) <= 3 and s->charges[BOW] > 0)
         {
            Move a('a', tile.first, tile.second, BOW);
            resultMoves.push_back(a);
         }
         if (dist == 1 and isCardinalMove(s->player_x, s->player_y, tile.first, tile.second))
         {
            Move a('a', tile.first, tile.second, SWORD);
            resultMoves.push_back(a);
         }
         if (dist <= 2 and s->charges[SCYTHE] > 0)
         {
            Move a('a', tile.first, tile.second, SCYTHE);
            resultMoves.push_back(a);
         }
         if (dist == 1 and s->charges[HAMMER] > 0)
         {
            Move a('a', tile.first, tile.second, HAMMER);
            resultMoves.push_back(a);
         }
      }
   }
   return resultMoves;
}

double TIME_THRESHOLD = 40.0; // miliseconds

void simulateNMoves(State *gameState, Move firstMove, int n, chrono::steady_clock::time_point time_start)
{
   simulateMove(gameState, firstMove);

   for (int i = 1; i < 20; i++)
   {
      if (gameState->on_exit)
         break;
      if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() >= TIME_THRESHOLD)
         break;
      vector<Move>
          validMoves = getPossibleMoves(gameState);
      assertm(validMoves.size() > 0, "simulateNMoves leads to 0 moves");
      Move move = validMoves[rand() % validMoves.size()];
      simulateMove(gameState, move);
   }
}

void simulateNMoves(State *gameState, int n, chrono::steady_clock::time_point time_start)
{
   for (int i = 0; i < 20; i++)
   {
      if (gameState->on_exit)
         break;
      if (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() >= TIME_THRESHOLD)
         break;
      vector<Move>
          validMoves = getPossibleMoves(gameState);
      assertm(validMoves.size() > 0, "simulateNMoves leads to 0 moves");
      Move move = validMoves[rand() % validMoves.size()];
      simulateMove(gameState, move);
   }
}

class Node
{
public:
   Node *parent;
   vector<Move> validMoves;
   unordered_map<int, Node *> children;
   int score;
   int simulations;
   int last_expanded;
   int terminal;
   int player_x;
   int player_y;
   Node(State *game, Node *parent = nullptr)
   {
      vector<Move> moves = getPossibleMoves(game);
      random_shuffle(moves.begin(), moves.end());
      this->validMoves = moves;
      this->score = 0;
      this->simulations = 1;
      this->last_expanded = -1;
      this->terminal = game->on_exit or game->player_HP < 0 ? 1 : -1;
      if (parent != nullptr)
         this->parent = parent;
      else
         this->parent = this;
      this->player_x = game->player_x;
      this->player_y = game->player_y;
   }
};

Node *expand(Node *node, State *game)
{
   node->last_expanded++;
   Move move = node->validMoves[node->last_expanded];
   simulateMove(game, move);
   node->children[node->last_expanded] = new Node(game, node);
   return node->children[node->last_expanded];
}

Node *bestChild(Node *node, State *game)
{
   Node *chosenSon;
   Move move;
   double bestScore = -1000000.0;
   for (auto son : node->children)
   {
      double score = (double)(son.second->score / (double)son.second->simulations) + 1.4 * sqrt((log(node->simulations) / son.second->simulations));
      if (score > bestScore)
      {
         chosenSon = son.second;
         bestScore = score;
         move = node->validMoves[son.first];
      }
   }
   simulateMove(game, move);
   return chosenSon;
}

Node *treePolicy(Node *node, State *game)
{
   while (node->terminal == -1)
   {
      if (node->last_expanded < (int)(node->validMoves.size() - 1))
      {
         return expand(node, game);
      }
      else
      {
         node = bestChild(node, game);
      }
   }
   return node;
}
void backPropagate(Node *current, int score)
{
   while (current->parent != current)
   {
      current->simulations++;
      current->score += score;
      current = current->parent;
   }
}

Move MCTS(State *gameState, chrono::steady_clock::time_point time_start)
{
   Node *root = new Node(gameState);
   while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() < TIME_THRESHOLD)
   {
      State gameCopy(gameState);
      Node *simulationNode = treePolicy(root, &gameCopy);
      int res;
      if (simulationNode->terminal)
         res = evaluateState(gameState, &gameCopy);
      else
      {
         simulateNMoves(&gameCopy, 15, time_start);
         res = evaluateState(gameState, &gameCopy);
      }
      backPropagate(simulationNode, res);
   }
   cerr << "sim: " << root->simulations << endl;
   Move move = root->validMoves[rand() % root->validMoves.size()];
   Node *chosenChild;
   double bestScore = -100000.0;
   for (auto son : root->children)
   {
      double score = son.second->simulations == 0 ? -1000 : (double)(son.second->score / (double)son.second->simulations);

      if (score > bestScore)
      {
         move = root->validMoves[son.first];
         bestScore = score;
         chosenChild = son.second;
      }
   }
   return move;
}

Move flatMC(State *gameState, vector<Move> validMoves, chrono::steady_clock::time_point time_start)
{
   vector<pair<int, int>> score(validMoves.size(), {0, 0}); //{score, count}
   while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() < TIME_THRESHOLD)
   {
      assertm(validMoves.size() > 0, "moves all right?");
      int moveIndex = rand() % validMoves.size();
      Move move = validMoves[moveIndex];

      State gameCopy(gameState);
      simulateNMoves(&gameCopy, move, 20, time_start);
      int result = evaluateState(gameState, &gameCopy);
      score[moveIndex] = {score[moveIndex].first + result,
                          score[moveIndex].second + 1};
   }
   cerr << "while finished" << endl;
   double bestScore = -10000.0;
   int bestIndex = 0, simulations = 0, biggestCount = 0;
   for (int i = 0; i < score.size(); i++)
   {
      simulations += score[i].second;

      if (score[i].second > 0 and ((double)(score[i].first / (double)score[i].second) > bestScore or ((double)(score[i].first / (double)score[i].second) == bestScore and score[i].second > biggestCount)))
      {
         bestScore = (double)(score[i].first / (double)score[i].second);
         bestIndex = i;
         biggestCount = score[i].second;
      }
   }
   cerr << "simulations: " << simulations << endl;
   return validMoves[bestIndex];
}

pair<pair<int, int>, int> getDistAndPath(int start_x, int start_y, int dest_x, int dest_y)
{
   cerr << "dest: " << dest_x << " " << dest_y << endl;
   queue<pair<int, int>> q;
   int visited[13][16];
   pair<int, int> parents[13][16];
   bool found = false;
   memset(visited, 0, sizeof(int) * 13 * 16);
   q.push({start_x, start_y});
   parents[start_y][start_x] = {-1, -1};
   visited[start_y][start_x] = 1;
   while (!q.empty())
   {
      auto t = q.front();
      if (t.first == dest_x and t.second == dest_y)
      {
         found = true;
         break;
      }
      q.pop();
      for (int i = 0; i < move_shift.size(); i++)
      {
         pair<int, int> new_tile = {t.first + move_shift[i].first, t.second + move_shift[i].second};
         if (new_tile.first < 0 or new_tile.first > 15 or new_tile.second < 0 or new_tile.second > 11)
            continue;
         if (!visited[new_tile.second][new_tile.first] and MAP[new_tile.second][new_tile.first] != UNKNOWN and MAP[new_tile.second][new_tile.first] != OBSTACLE)
         {
            visited[new_tile.second][new_tile.first] = 1;
            q.push(new_tile);
            parents[new_tile.second][new_tile.first] = t;
         }
      }
   }
   if (!found)
   {
      return {{-1, -1}, 1000};
   }
   // Reconstruct the path
   pair<int, int> ending = {dest_x, dest_y};
   list<pair<int, int>> path;
   int dist = 0;
   while (parents[ending.second][ending.first] != make_pair(-1, -1))
   {
      path.push_back(ending);
      ending = parents[ending.second][ending.first];
      dist++;
   }
   return {path.back(), dist};
}

Move heuristic(State *game, vector<Move> moves, chrono::steady_clock::time_point time_start)
{
   int dmg = 0;
   Move chosenMove;
   for (auto move : moves) // most dmg
   {
      move.print(true);
      State *gameCopy = new State(game);
      int dealing = gameCopy->applyPlayerMove(move);
      if (gameCopy->entity_info[move.y][move.x].first.type == BOX and move.weapon != SWORD)
         continue;

      if (dealing > dmg)
      {
         dmg = dealing;
         chosenMove = move;
      }
      delete gameCopy;
   }
   if (chosenMove.x == -1)
   {
      int dist = 1000;
      if (game->treasure.size() > 0)
      {
         pair<int, int> dest;
         for (auto el : game->treasure)
         {
            cerr << "tre: " << el.first.first << " " << el.first.second << " " << el.second << endl;
            auto t = getDistAndPath(game->player_x, game->player_y, el.first.second, el.first.first);
            cerr << "finished bfs" << endl;
            if (t.second < dist)
            {
               dist = t.second;
               dest = t.first;
            }
         }
         cerr << "bfs: " << dist << " " << dest.first << " " << dest.second << endl;
         chosenMove = Move('m', dest.first, dest.second);
      }
      if (dist == 1000)
      {
         State *gameCopy = new State(game);
         chosenMove = flatMC(gameCopy, moves, time_start);
         cerr << "finished MC" << endl;
         delete gameCopy;
      }
   }
   return chosenMove;
}

State *gameState = nullptr;
int globalTurn = 0;

int main()
{
   srand(time(NULL));
   memset(MAP, -1, sizeof(int) * 13 * 17); // SET THE WHOLE MAP TO UNKNOWN

   while (1)
   {
      chrono::steady_clock::time_point begin = chrono::steady_clock::now();
      int x, y, health, score, charges_hammer, charges_scythe, charges_bow;
      cin >> x >> y >> health >> score >> charges_hammer >> charges_scythe >> charges_bow;
      cin.ignore();
      int visible_entities; // the number of visible entities
      cin >> visible_entities;
      cin.ignore();
      vector<pair<int, int>> monsters;
      map<pair<int, int>, bool> treasure;
      vector<pair<int, int>> other;
      vector<vector<pair<Entity, Entity>>> info(12, vector<pair<Entity, Entity>>(16, make_pair(Entity(), Entity())));
      for (int i = 0; i < visible_entities; i++)
      {
         int ex, ey, etype, evalue;
         cin >> ex >> ey >> etype >> evalue;
         cin.ignore();
         int hp = evalue;
         Entity e(etype, evalue, ex, ey, hp);
         if (etype >= 7)
         {
            info[ey][ex].first = e;
            monsters.push_back({ex, ey});
         }
         else
         {
            if (etype == OBSTACLE)
               MAP[ey][ex] = OBSTACLE;
            if (etype == TREASURE)
               treasure.insert({{ey, ex}, true});
            info[ey][ex].second = e;
            other.push_back({ex, ey});
         }
      }
      // UPDATE MAP
      for (int i = max(y - 3, 0); i <= min(y + 3, 11); i++)
         for (int j = max(x - 3, 0); j <= min(x + 3, 15); j++)
         {
            if (info[i][j].second.type == 1)
               MAP[i][j] = OBSTACLE;
            else
               MAP[i][j] = 0;
         }
      if (globalTurn == 0)
         gameState = new State(health, x, y, score, {10000000, charges_hammer, charges_scythe, charges_bow}, monsters, info, treasure);
      else
      {
         // DELETE OLD MONSTER KNOLEDGE
         for (auto cords : gameState->monsters)
         {
            gameState->entity_info[cords.second][cords.first].first = Entity();
         }
         // ADD CURRENT KNOWLEDGE
         gameState->monsters = monsters;
         for (auto cords : monsters)
         {
            gameState->entity_info[cords.second][cords.first].first = info[cords.second][cords.first].first;
         }
         // ADD NEW ENTITIES
         for (auto cords : other)
            if (gameState->entity_info[cords.second][cords.first].second.type == -1)
            {
               gameState->entity_info[cords.second][cords.first].second = info[cords.second][cords.first].second;
               if (info[cords.second][cords.first].second.type == TREASURE)
                  gameState->treasure.insert({{cords.second, cords.first}, true});
            }
      }

      vector<Move> moves = getPossibleMoves(gameState);

      State gameCopy(gameState);
      Move selected = flatMC(gameState, moves, begin);
      // Move selected = heuristic(gameState, moves, begin);
      selected.print();
      simulateMove(gameState, selected);
      cerr << "move simulated" << endl;
      globalTurn++;
   }
}