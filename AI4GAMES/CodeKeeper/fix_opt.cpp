#pragma GCC optimize("Ofast", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC option("march=native", "tune=native", "no-zero-upper") // Enable AVX
#pragma GCC target("avx2")                                         // Enable AVX
#include <bits/stdc++.h>
#include <x86intrin.h> //AVX/SSE Extensions
#include <bits/stdc++.h>
#define assertm(exp, msg) assert(((void)msg, exp))
using namespace std;

int MAP[13][17];

vector<pair<int, int>> move_shift = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
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
   EMPTY = -2,
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
   if (abs(current_x - new_x) + abs(current_y - new_y) == 1) // not equal to include staying in place as well
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
   set<pair<int, int>> visited;
   int player_HP;
   vector<int> charges;
   int score;
   int player_x;
   int player_y;
   bool on_exit;
   int turn;
   bool exit_available;
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
      this->turn = s->turn;
      this->visited = s->visited;
      this->exit_available = s->exit_available;
   }
   State(int hp, int x, int y, int score, vector<int> charges, vector<pair<int, int>> monsters, vector<vector<pair<Entity, Entity>>> info)
   {
      this->entity_info = info;
      this->monsters = monsters;
      this->player_HP = hp;
      this->charges = charges;
      this->score = score;
      this->player_x = x;
      this->player_y = y;
      this->on_exit = false;
      this->turn = 0;
      this->visited = {};
      this->exit_available = false;
   }
   pair<int, int> applyPlayerMove(Move move) // -> {dmg dealt, monsters hit}
   {
      this->turn++;
      int dmgDealt = 0;
      int monsters_hit = 0;
      if (move.type == 'm')
      {
         this->player_x = move.x;
         this->player_y = move.y;
         visited.insert({move.x, move.y});
         if (this->entity_info[move.y][move.x].second.type != -1) // handle pick up
         {
            this->score += scorePerEntity[this->entity_info[move.y][move.x].second.type]; // add score
            switch (this->entity_info[move.y][move.x].second.type)
            {
            case EXIT:
               this->on_exit = true;
               break;
            case TREASURE:
               break;
            case POTION:
               this->player_HP = min(20, this->player_HP + 10);
               break;
            case HAMMER_CHARGE:
               this->charges[HAMMER]++;
               break;
            case SCYTHE_CHARGE:
               this->charges[SCYTHE]++;
               break;
            case BOW_CHARGE:
               this->charges[BOW]++;
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
               monsters_hit = 1;
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
                  monsters_hit++;
                  dmgDealt += min(this->entity_info[tile.second][tile.first].first.HP, dmgWeapon[HAMMER]);
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
                  monsters_hit++;
                  dmgDealt += min(this->entity_info[tile.second][tile.first].first.HP, dmgWeapon[SCYTHE]);
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
               monsters_hit = 1;
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
      return {dmgDealt, monsters_hit};
   }
   void removeMonster(int x, int y)
   {
      for (unsigned i = 0; i < this->monsters.size(); i++)
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
         //   cerr << "player not found" << endl;
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
      //   cerr << "path restored" << endl;
      return path.back();
   }

   pair<int, int> simulateMonstersMove(int monster_x = -1, int monster_y = -1)
   {
      if (this->on_exit)
         return {monster_x, monster_y};

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
               if (cords == make_pair(monster_x, monster_y))                                                                          // return new position of monster
                  return monster_move;
            }
         }
      }
      return {monster_x, monster_y};
   }
};

vector<pair<int, int>> getTilesInSight(int player_x, int player_y)
{
   vector<pair<int, int>> tiles;
   for (int y = max(player_y - 3, 0); y <= min(player_y + 3, 11); y++)
      for (int x = min(player_x + 3, 15); x >= max(player_x - 3, 0); x--)
      {
         if (MAP[y][x] != UNKNOWN)
            tiles.push_back({x, y});
      }
   return tiles;
}

vector<Move> getPossibleMoves(State *s)
{
   vector<pair<int, int>> tilesToConsider = getTilesInSight(s->player_x, s->player_y);
   vector<Move> resultMoves;
   for (auto tile : tilesToConsider) // tile = (x, y)
   {
      if (MAP[tile.second][tile.first] != OBSTACLE and s->entity_info[tile.second][tile.first].first.type == -1 and s->entity_info[tile.second][tile.first].second.type != 1 and isCardinalMove(s->player_x, s->player_y, tile.first, tile.second)) // cardinal move without obstacle
      {
         Move m('m', tile.first, tile.second);
         resultMoves.push_back(m);
      }
      int dist = getDistance(tile, {s->player_x, s->player_y});
      if (s->entity_info[tile.second][tile.first].first.type != -1) // consider attacking monster or a box
      {
         if (dist <= 2 and s->charges[SCYTHE] > 0)
         {
            Move a('a', tile.first, tile.second, SCYTHE);
            resultMoves.push_back(a);
         }
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
      }
      if (dist == 1 and s->charges[HAMMER] > 0)
      {
         Move a('a', tile.first, tile.second, HAMMER);
         resultMoves.push_back(a);
      }
   }
   return resultMoves;
}
double TIME_THRESHOLD = 53.0; // miliseconds

void simulateMove(State *startState, Move move)
{
   // PLAYER MOVE
   startState->applyPlayerMove(move);
   // MONSTERS MOVE
   startState->simulateMonstersMove();
}

int count_uknown_fields(int tile_x, int tile_y)
{
   int result = 0;
   for (int y = max(tile_y - 3, 0); y <= min(tile_y + 3, 11); y++)
      for (int x = min(tile_x + 3, 15); x >= max(tile_x - 3, 0); x--)
      {
         if (MAP[y][x] == UNKNOWN)
            result++;
      }
   return result;
}

struct compare
{
   bool operator()(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b)
   {
      return a.first > b.first;
   }
};

struct compare_v2
{
   bool operator()(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
   {
      if (a.first.first == b.first.first)
         return a.first.second > b.first.second;
      return a.first.first > b.first.first;
   }
};

bool BOX_LEVEL = false;

unordered_map<int, pair<pair<int, int>, pair<int, int>>> getDistAndPath(int start_x, int start_y, State *game)
{
   unordered_map<int, pair<pair<int, int>, pair<int, int>>> best_per_type; // type -> {dest, {value, true_distance}}
   unordered_map<int, int> fields_uncovevered;
   for (int i = -2; i < 15; i++)
   {
      best_per_type[i] = {{-1, -1}, {1000, 1000}};
      fields_uncovevered[i] = 0;
   }

   // priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, compare> q;
   priority_queue<pair<pair<int, int>, pair<int, int>>, vector<pair<pair<int, int>, pair<int, int>>>, compare_v2> q;
   //    queue<pair<pair<int, int>, pair<int, int>>> q;
   // ((value, true_distance), (x, y))
   pair<int, int> parents[13][17];
   int visited[13][17];
   memset(visited, 0, sizeof(int) * 13 * 17);
   q.push({{0, 0}, {start_x, start_y}});
   parents[start_y][start_x] = {-1, -1};
   visited[start_y][start_x] = 1;
   while (!q.empty())
   {
      auto t = q.top();
      q.pop();
      pair<int, int> ending = {t.second.first, t.second.second};
      list<pair<int, int>> path;
      if (t.second.first != game->player_x or t.second.second != game->player_y)
      {
         if (best_per_type[game->entity_info[t.second.second][t.second.first].second.type].second.first > t.first.first)
         {
            while (parents[ending.second][ending.first] != make_pair(-1, -1))
            {
               path.push_back(ending);
               ending = parents[ending.second][ending.first];
            }
            best_per_type[game->entity_info[t.second.second][t.second.first].second.type].second.first = t.first.first;
            best_per_type[game->entity_info[t.second.second][t.second.first].second.type].second.second = t.first.second;
            best_per_type[game->entity_info[t.second.second][t.second.first].second.type].first = path.back();
         }
         //  cerr << t.second.first << " " << t.second.second << endl;
         if (!game->visited.count({t.second.first, t.second.second}) and game->entity_info[t.second.second][t.second.first].second.type != EXIT and (best_per_type[EMPTY].second.first > t.first.first or (best_per_type[EMPTY].second.first == t.first.first and count_uknown_fields(t.second.first, t.second.second) > fields_uncovevered[game->entity_info[t.second.second][t.second.first].second.type])))
         {
            // cerr << "entered" << endl;
            if (game->entity_info[t.second.second][t.second.first].second.type == -1 and count_uknown_fields(t.second.first, t.second.second) == 0 and BOX_LEVEL == false)
            {
               cerr << "SKIPPING UNNECESSERY MOVE: " << t.second.first << " " << t.second.second << endl;
            }
            else
            {
               if (path.empty())
               {
                  ending = {t.second.first, t.second.second};
                  while (parents[ending.second][ending.first] != make_pair(-1, -1))
                  {
                     path.push_back(ending);
                     ending = parents[ending.second][ending.first];
                  }
               }
               if (game->turn < 80 or game->exit_available or count_uknown_fields(t.second.first, t.second.second) > 1)
               {
                  cerr << "considering: " << t.second.first << " " << t.second.second << endl;
                  fields_uncovevered[game->entity_info[t.second.second][t.second.first].second.type] = count_uknown_fields(t.second.first, t.second.second);
                  best_per_type[EMPTY].second.first = t.first.first;
                  best_per_type[EMPTY].second.second = t.first.second;
                  best_per_type[EMPTY].first = path.back();
               }
               else
               {
                  // cerr << "skipping: " <<  t.second.first << " " <<  t.second.second << endl;
               }
            }
         }
      }

      if (game->entity_info[t.second.second][t.second.first].second.type == EXIT)
      { // no way through exit
         continue;
      }
      random_shuffle(move_shift.begin(), move_shift.end()); // bring back + 1?
      for (unsigned i = 0; i < move_shift.size(); i++)
      {
         pair<int, int> new_tile = {t.second.first + move_shift[i].first, t.second.second + move_shift[i].second};
         if (new_tile.first < 0 or new_tile.first > 15 or new_tile.second < 0 or new_tile.second > 11 or (new_tile.first == game->player_x and new_tile.second == game->player_y))
            continue;
         int penaltyMultiplier = 1;
         if (!visited[new_tile.second][new_tile.first] and MAP[new_tile.second][new_tile.first] != UNKNOWN and MAP[new_tile.second][new_tile.first] != OBSTACLE)
         {
            visited[new_tile.second][new_tile.first] = 1;
            for (int i = 0; i < game->monsters.size(); i++)
            {
               pair<int, int> cords = game->monsters[i];
               int dist = getViewDistance({new_tile.first, new_tile.second}, cords);
               if (dist <= attackRange[game->entity_info[cords.second][cords.first].first.type] and attackRange[game->entity_info[cords.second][cords.first].first.type] > 1 and game->charges[BOW] == 0) // if tile in shooter range, penalize
               {
                  cerr << "penalizing: " << new_tile.first << " " << new_tile.second << endl;
                  t.first.first += 4 * penaltyMultiplier;
                  penaltyMultiplier++;
               }
            }
            // if(game->entity_info[new_tile.second][new_tile.first].second.type == EXIT and game->turn < 130 and game->player_HP > 8){
            //     t.first += 10;
            // }
            if (game->entity_info[new_tile.second][new_tile.first].first.type == BOX)
            {
               // cerr << "have to go through a box" << endl;
               t.first.first += 1;
               t.first.second += 1;
            }
            if (game->entity_info[new_tile.second][new_tile.first].second.type >= 4 and game->entity_info[new_tile.second][new_tile.first].second.type <= 6)
               t.first.first -= 1;
            q.push({{t.first.first + 1, t.first.second + 1}, new_tile});
            parents[new_tile.second][new_tile.first] = t.second;
         }
      }
   }
   return best_per_type;
}

int evaluateState(State *game, State *gameCopy)
{
   int result = gameCopy->score;
   result += 10 * (gameCopy->player_HP - game->player_HP); // avoid dmg in mc
   return result;
}

void simulateNMoves(State *gameState, Move firstMove, int n, chrono::steady_clock::time_point time_start)
{
   simulateMove(gameState, firstMove);

   for (int i = 1; i < n; i++)
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

Move flatMC(State *gameState, vector<Move> validMoves, chrono::steady_clock::time_point time_start)
{
   vector<pair<int, int>> score(validMoves.size(), {0, 0}); //{score, count}
   while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() < TIME_THRESHOLD)
   {
      assertm(validMoves.size() > 0, "moves all right?");
      int moveIndex = rand() % validMoves.size();
      Move move = validMoves[moveIndex];

      State gameCopy(gameState);
      simulateNMoves(&gameCopy, move, 5, time_start);
      int result = evaluateState(gameState, &gameCopy);
      score[moveIndex] = {score[moveIndex].first + result,
                          score[moveIndex].second + 1};
   }
   // cerr << "while finished" << endl;
   double bestScore = -10000.0;
   int bestIndex = 0, simulations = 0, biggestCount = 0;
   for (int i = 0; i < score.size(); i++)
   {
      simulations += score[i].second;
      if (gameState->entity_info[validMoves[i].y][validMoves[i].x].second.type == EXIT)
         continue;
      if (score[i].second > 0 and ((double)(score[i].first / (double)score[i].second) > bestScore or ((double)(score[i].first / (double)score[i].second) == bestScore and score[i].second > biggestCount)))
      {
         bestScore = (double)(score[i].first / (double)score[i].second);
         bestIndex = i;
         biggestCount = score[i].second;
      }
   }
   // cerr << "simulations: " << simulations << endl;
   return validMoves[bestIndex];
}

Move heuristic(State *game, vector<Move> moves, chrono::steady_clock::time_point time_start)
{
   int dmg = 0;
   Move chosenMove;
   int dist = 1000;
   pair<int, int> dest = {-1, -1};
   bool potion_not_found = false;

   unordered_map<int, pair<pair<int, int>, pair<int, int>>> best_per_type = getDistAndPath(game->player_x, game->player_y, game);
   cerr << "CLOSEST TREASURE: " << best_per_type[TREASURE].second.first << " " << best_per_type[TREASURE].second.second << endl;

   if (best_per_type[EXIT].second.first != 1000)
      game->exit_available = true;
   cerr << best_per_type[EXIT].first.first << " " << best_per_type[EXIT].first.second << endl;
   for (auto move : moves) // most dmg
   {
      if (move.type == 'm' or (best_per_type[EXIT].second.first != 1000 and best_per_type[EXIT].second.second > 150 - (game->turn + 4)))
         continue;
      move.print(true);
      State *gameCopy = new State(game);
      if (gameCopy->entity_info[move.y][move.x].first.type == BOX and move.weapon != SWORD and !BOX_LEVEL)
         continue;

      State *deathTest = new State(game);
      simulateMove(deathTest, move);
      if (deathTest->player_HP <= 0 or (abs(deathTest->player_HP - game->player_HP) >= 5 and game->player_HP <= 10))
      { // if the move kills us or deals > 5 dmg to us, skip
         continue;
      }
      delete deathTest;

      auto new_pos = gameCopy->simulateMonstersMove(move.x, move.y);
      if (!BOX_LEVEL and attackRange[gameCopy->entity_info[new_pos.second][new_pos.first].first.type] < getViewDistance({game->player_x, game->player_y}, {move.x, move.y})) // dont't attack if we are not in danger
      {
         // cerr << "skipped attack" << endl;
         continue;
      }

      gameCopy = new State(game);
      auto atck = gameCopy->applyPlayerMove(move);
      int dealing = atck.first;
      int monsters_hit = atck.second;
      cerr << "attack: " << move.weapon << " dmg: " << dealing << endl;

      if (move.weapon == HAMMER and monsters_hit < 2)
      {
         cerr << "skipped hammer attack" << endl;
         continue;
      }

      if (dealing > dmg) // most dmg
      {
         if (move.weapon == BOW and (attackRange[game->entity_info[move.y][move.x].first.type] < 2 or getViewDistance({game->player_x, game->player_y}, {move.x, move.y}) > 2))
            continue;
         dmg = dealing;
         chosenMove = move;
      }
      else if (dealing == dmg and move.weapon == SWORD)
         chosenMove = move;
      else if (dealing == dmg and getViewDistance({gameCopy->player_x, gameCopy->player_y}, {move.x, move.y}) <= attackRange[game->entity_info[move.y][move.x].first.type] and chosenMove.type == BOW) // priority on the one hitting us
         chosenMove = move;
      delete gameCopy;
   }
   //    cerr << "before whole: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() << endl;
   if (chosenMove.x == -1)
   {
      // type -> {dest, distance}
      cerr << "after whole: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() << endl;
      if (game->player_HP <= 10) // low hp, go for potion
      {
         dist = best_per_type[POTION].second.second;
         dest = best_per_type[POTION].first;
         if (dist == 1000)
         {
            potion_not_found = true;
            cerr << "potion not found " << endl;
         }
         else
            cerr << "looking for potion " << endl;
      }
      chosenMove = Move('m', dest.first, dest.second);
      if (dist == 1000) // nearest treasure
      {
         cerr << "considering treasure???? " << endl;
         dist = best_per_type[TREASURE].second.second;
         dest = best_per_type[TREASURE].first;
         if (dist != 1000)
         {
            cerr << "found closest treasure" << endl;
         }
         chosenMove = Move('m', dest.first, dest.second);
      }
      if (dist == 1000 or (potion_not_found and game->charges[BOW] == 0) or (best_per_type[EXIT].second.first != 1000 and best_per_type[EXIT].second.second > 150 - (game->turn + 7))) // nearest exit
      {
         dist = best_per_type[EXIT].second.second;
         dest = best_per_type[EXIT].first;
         if (dist > 150 - (game->turn + 10) or potion_not_found)
         {
            chosenMove = Move('m', dest.first, dest.second);
            cerr << "here: " << dist << endl;
         }
         else
            dist = 1000;

         if (dist != 1000)
         {
            cerr << "found closest EXIT" << endl;
         }
      }
      if (dist == 1000 or (best_per_type[EXIT].second.first == 1000 and game->turn > 80)) // nearest unvisited field
      {
         dist = best_per_type[EMPTY].second.second;
         dest = best_per_type[EMPTY].first;
         chosenMove = Move('m', dest.first, dest.second);
         if (dist != 1000)
         {
            cerr << "found closest empty" << endl;
         }
      }
      Move moveBeforeSwitch = chosenMove;
      moveBeforeSwitch.print(true);
      if (dist != 1000 and chosenMove.type == 'm')
      {
         cerr << "considering switching to attack" << endl;
         State *gameCopy = new State(game);
         simulateMove(gameCopy, chosenMove);
         if (game->player_HP > gameCopy->player_HP)
         {
            for (auto move : moves) // most dmg
            {
               if (move.type == 'm')
                  continue;
               State *gameCopy2 = new State(game);
               if (gameCopy2->entity_info[move.y][move.x].first.type == BOX)
                  continue;

               State *deathTest = new State(game);
               simulateMove(deathTest, move);
               if (deathTest->player_HP <= 0 or (abs(deathTest->player_HP - game->player_HP) >= 5 and game->player_HP <= 10))
               { // if the move kills us or deals > 5 dmg to us, skip
                  continue;
               }
               delete deathTest;

               auto atck = gameCopy2->applyPlayerMove(move);
               int dealing = atck.first;
               int monsters_hit = atck.second;

               if (move.weapon == HAMMER and monsters_hit < 1)
               {
                  cerr << "skipped hammer attack" << endl;
                  continue;
               }

               if (dealing >= dmg and getViewDistance({gameCopy->player_x, gameCopy->player_y}, {move.x, move.y}) <= attackRange[game->entity_info[move.y][move.x].first.type]) // priority on the one hitting us
               {
                  if (move.weapon == BOW and ((attackRange[game->entity_info[move.y][move.x].first.type] < 2 and game->player_HP > 3) or getViewDistance({gameCopy->player_x, gameCopy->player_y}, {move.x, move.y}) > 2)) // and  and abs(game->player_HP - gameCopy->player_HP) < 4)
                     continue;
                  dealing = dmg;
                  chosenMove = move;
               }
               else if (dealing <= dmg and getViewDistance({gameCopy->player_x, gameCopy->player_y}, {move.x, move.y}) <= attackRange[game->entity_info[move.y][move.x].first.type] and game->entity_info[move.y][move.x].first.HP <= dealing and getViewDistance({gameCopy->player_x, gameCopy->player_y}, {move.x, move.y}) <= attackRange[game->entity_info[move.y][move.x].first.type]) // priority on kills
                  chosenMove = move;
               delete gameCopy2;
            }
         }
         if (chosenMove.type == 'a')
            cerr << "switched to attack move" << endl;
      }
      State *gameCopy = new State(game);
      if (dist != 1000)
         simulateMove(gameCopy, chosenMove);
      if (dist == 1000 or gameCopy->player_HP <= 0)
      { // do something better
         if (moveBeforeSwitch.x != chosenMove.x and moveBeforeSwitch.y != chosenMove.y)
            chosenMove = moveBeforeSwitch;
         else
         {
            if (best_per_type[EXIT].second.first != 1000)
            {
               dest = best_per_type[EXIT].first;
               chosenMove = Move('m', dest.first, dest.second);
            }
            else
            {
               cerr << "trying MC" << endl;
               State *gameCopy = new State(game);
               chosenMove = flatMC(gameCopy, moves, time_start);
               delete gameCopy;
            }
         }
      }
   }
   return chosenMove;
}

State *gameState = nullptr;
State *lastGame = nullptr;
int globalTurn = 0;

int main()
{
   srand(time(NULL));
   memset(MAP, -1, sizeof(int) * 13 * 17); // SET THE WHOLE MAP TO UNKNOWN
   int boxes = 0;
   while (1)
   {

      int x, y, health, score, charges_hammer, charges_scythe, charges_bow;
      cin >> x >> y >> health >> score >> charges_hammer >> charges_scythe >> charges_bow;
      if (gameState != nullptr)
      {
         gameState->player_HP = health;
         gameState->player_x = x;
         gameState->player_y = y;
         gameState->score = score;
         gameState->charges = {10000000, charges_hammer, charges_scythe, charges_bow};
      }
      cin.ignore();
      // cerr << x << " " << y << " " << health << " " << score << " " << charges_hammer << " "<< " " << charges_scythe << " " << charges_bow << endl;
      int visible_entities; // the number of visible entities
      cin >> visible_entities;
      cin.ignore();
      // /cerr << visible_entities << endl;
      vector<pair<int, int>> monsters = {};
      vector<pair<int, int>> other = {};
      vector<vector<pair<Entity, Entity>>> info(12, vector<pair<Entity, Entity>>(16, make_pair(Entity(), Entity())));
      for (int i = 0; i < visible_entities; i++)
      {
         int ex, ey, etype, evalue;
         cin >> ex >> ey >> etype >> evalue;
         cin.ignore();
         if (etype == BOX)
            boxes++;
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
            info[ey][ex].second = e;
            other.push_back({ex, ey});
         }
      }
      chrono::steady_clock::time_point begin = chrono::steady_clock::now();
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
      {
         gameState = new State(health, x, y, score, {10000000, charges_hammer, charges_scythe, charges_bow}, monsters, info);
         if (boxes >= 39)
            BOX_LEVEL = true;
      }
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
            gameState->entity_info[cords.second][cords.first].second = info[cords.second][cords.first].second;
      }

      vector<Move> moves = getPossibleMoves(gameState);
      Move selected = heuristic(gameState, moves, begin);
      // Move selected = moves[rand() % moves.size()];
      selected.print();
      gameState->applyPlayerMove(selected);
      // cerr << "move simulated" << endl;
      globalTurn++;
   }
}