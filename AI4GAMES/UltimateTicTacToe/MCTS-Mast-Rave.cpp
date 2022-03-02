#include <bits/stdc++.h>

using namespace std;

const int row1 = 7, row2 = 56, row3 = 448;
const int col1 = 292, col2 = 146, col3 = 73;
const int diag1 = 273, diag2 = 84;

double ROUND_TIME = 99.0;     // miliseconds
double FIRST_ROUND = 999.0;   // miliseconds
double TIME_THRESHOLD = 99.0; // miliseconds

const double epsilon = 30;

class UltimateTicTacToe
{
public:
   vector<unordered_set<int>> rows, columns, diagonals;
   unordered_map<int, int> rowsCount, columnsCount, diagonalsCount;
   vector<vector<pair<int, int>>> board;
   vector<int> TicTacToeWins;

   int gameEnd(int moveCount)
   {
      for (int i = 0; i < 3; i++)
      {
         if (rowsCount[i] == 3 and rows[i].size() == 1)
            return (*rows[i].begin());
         if (columnsCount[i] == 3 and columns[i].size() == 1)
            return (*columns[i].begin());
         if (i < 2 and diagonalsCount[i] == 3 and diagonals[i].size() == 1)
            return (*diagonals[i].begin());
      }

      if (moveCount == 1)
         return TicTacToeWins[0] > TicTacToeWins[1] ? 0 : 1;

      return -1;
   }

   int smallGameEnd(pair<int, int> smallBoard, int player)
   {
      int toCheck = player == 0 ? smallBoard.first : smallBoard.second;
      if ((toCheck & row1) == row1 or (toCheck & row2) == row2 or (toCheck & row3) == row3 or (toCheck & col1) == col1 or (toCheck & col2) == col2 or (toCheck & col3) == col3 or (toCheck & diag1) == diag1 or (toCheck & diag2) == diag2)
         return player;
      return -1;
   }

   UltimateTicTacToe()
   {
      rows.resize(3);
      columns.resize(3);
      diagonals.resize(2);
      board = vector<vector<pair<int, int>>>(3, vector<pair<int, int>>(3, {0, 0}));
      TicTacToeWins.resize(2, 0);
   }

   UltimateTicTacToe(UltimateTicTacToe &toCopy)
   {
      rows = toCopy.rows;
      columns = toCopy.columns;
      diagonals = toCopy.diagonals;
      rowsCount = toCopy.rowsCount;
      columnsCount = toCopy.columnsCount;
      diagonalsCount = toCopy.diagonalsCount;
      board = toCopy.board;
      TicTacToeWins = toCopy.TicTacToeWins;
   }

   int moveSmall(int row, int col, int player, vector<pair<int, int>> &moves)
   {
      int smallRow = row % 3, smallCol = col % 3;
      int shift = (1 << (3 * smallRow + smallCol));
      auto oldState = board[row / 3][col / 3];
      board[row / 3][col / 3] = {player != 0 ? oldState.first : (oldState.first | shift), player != 1 ? oldState.second : (oldState.second | shift)};
      int res = smallGameEnd(board[row / 3][col / 3], player);

      if (res != -1)
      { // delete rest of moves from a small board if somebody won
         vector<int> indexes;
         int counter = 0;
         for (int i = 0; i < moves.size(); i++)
         {
            if (moves[i].first / 3 == row / 3 and moves[i].second / 3 == col / 3 and (moves[i] != make_pair(row, col)))
               indexes.push_back(i);
         }
         for (auto index : indexes)
         {
            moves.erase(moves.begin() + index - counter);
            counter++;
         }
      }
      return res;
   }

   int getPossibleMovesCount(int row, int col)
   {
      int result = 9;
      if (smallGameEnd(board[row][col], 0) == 0 or smallGameEnd(board[row][col], 1) == 1)
         return 0;
      for (int i = 0; i < 9; i++)
         result -= ((board[row][col].first & (1 << i)) or (board[row][col].second & (1 << i)));

      return result;
   }

   int move(int row, int col, int player, vector<pair<int, int>> &moves, bool debug = false)
   {
      int boardRow = row / 3, boardCol = col / 3;
      int smallRow = row % 3, smallCol = col % 3;

      // cerr << "before small move size: " << moves.size() << endl;
      int response = moveSmall(row, col, player, moves);
      // cerr << "after small move size: " << moves.size() << endl;

      if (response != -1)
         TicTacToeWins[response]++;

      if (response != -1)
      {
         rows[boardRow].insert(response);
         columns[boardCol].insert(response);
         rowsCount[boardRow]++;
         columnsCount[boardCol]++;
         if (boardRow == boardCol)
         {
            diagonals[0].insert(response);
            diagonalsCount[0]++;
         }
         if (boardRow == abs(2 - boardCol))
         {
            diagonals[1].insert(response);
            diagonalsCount[1]++;
         }
      }
      return gameEnd(moves.size());
   }
};

void updateActions(vector<pair<int, int>> &actions, pair<int, int> move)
{
   int indexToDelete = -1;
   for (int i = 0; i < actions.size(); i++)
   {
      if (actions[i] == move)
         indexToDelete = i;
   }
   if (indexToDelete == -1)
   {
      cerr << "move: " << move.first << " " << move.second << endl;
      for (auto action : actions)
      {
         cerr << "action: " << action.first << " " << action.second << endl;
      }
   }
   assert(indexToDelete != -1);
   actions.erase(actions.begin() + indexToDelete);
}

vector<string> usedMoves;
unordered_map<string, pair<int, int>> MAST; // string(row, col) -> {wins, number of uses}

pair<int, int> chooseMoveWithMast(vector<pair<int, int>> validActions)
{
   vector<pair<double, pair<int, int>>> scoredMoves;
   for (auto move : validActions)
   {
      double wins = MAST[to_string(move.first) + to_string(move.second)].first;
      double uses = max(MAST[to_string(move.first) + to_string(move.second)].second, 0);
      scoredMoves.push_back({wins / uses, move});
   }
   sort(scoredMoves.begin(), scoredMoves.end());
   int p = rand() % 100;
   if (p > epsilon)
      return scoredMoves.back().second;
   return validActions[rand() % validActions.size()];
}

int simulateGame(UltimateTicTacToe &game, vector<pair<int, int>> &validActions, pair<int, int> lastMove, int me, chrono::steady_clock::time_point time_start)
{
   int player = me;
   int result;
   usedMoves.push_back(to_string(lastMove.first) + to_string(lastMove.second));
   while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() < TIME_THRESHOLD)
   {
      int moveRowSmall = lastMove.first % 3, moveColSmall = lastMove.second % 3;
      vector<pair<int, int>> validActionsSmall;

      if (game.getPossibleMovesCount(moveRowSmall, moveColSmall) > 0)
      { // get moves limited to the small board forced by last move
         for (auto mv : validActions)
         {
            if (mv.first / 3 == moveRowSmall and mv.second / 3 == moveColSmall)
               validActionsSmall.push_back(mv);
         }
      }
      if (validActionsSmall.size() == 0)
         validActionsSmall = validActions;

      pair<int, int> move = chooseMoveWithMast(validActionsSmall);

      result = game.move(move.first, move.second, player, validActions);
      usedMoves.push_back(to_string(move.first) + to_string(move.second));
      if (result != -1)
      {
         for (auto mv : usedMoves)
         {
            pair<int, int> prev = MAST[mv];
            MAST[mv] = {prev.first + (result == me), prev.second + 1};
         }
         return result == me ? 1 : -1;
      }

      //   cerr << "deleting2: " << move.first << " " << move.second << endl;
      updateActions(validActions, move);

      // cerr << "sim move: " << move.first << " " << move.second << endl;
      //    cerr << "actions size: " << validActions.size() << endl;
      lastMove = move;
      player = 1 - player;
   }
   return 0;
}

class Node
{
public:
   vector<pair<int, int>> validmoves;
   vector<pair<int, int>> allMoves;
   unordered_map<string, int> amafWins;
   vector<int> wins;
   int simulations;
   int amafSimulations;
   int last_expanded;
   int terminal;
   Node *parent;
   unordered_map<int, Node *> sons;
   Node(vector<pair<int, int>> moves, UltimateTicTacToe &game, Node *ancestor = nullptr, pair<int, int> last_move = {-1, -1})
   {
      allMoves = moves;
      if (last_move == make_pair(-1, -1))
      {
         random_shuffle(moves.begin(), moves.end());
         validmoves = moves;
      }
      else
      {
         vector<pair<int, int>> validActionsSmall;
         int opponentRowSmall = last_move.first % 3, opponentColSmall = last_move.second % 3;
         if (game.getPossibleMovesCount(opponentRowSmall, opponentColSmall) > 0)
         { // get moves limited to the small board forced by opponent
            for (auto mv : moves)
            {
               if (mv.first / 3 == opponentRowSmall and mv.second / 3 == opponentColSmall)
                  validActionsSmall.push_back(mv);
            }
         }

         if (validActionsSmall.size() == 0)
            validActionsSmall = moves;

         random_shuffle(validActionsSmall.begin(), validActionsSmall.end());

         validmoves = validActionsSmall;
      }
      wins.resize(2, 0);
      simulations = 1;
      amafSimulations = 1;
      last_expanded = -1;
      terminal = -1;
      if (ancestor)
         parent = ancestor;
   }
};

void updateAmaf(Node *current, int score)
{
   while (current)
   {
      current->amafSimulations++;
      for (auto move : usedMoves)
      {
         current->amafWins[move] += score;
      }
      current = current->parent;
   }
}

class NodeWithMove
{
public:
   Node *node;
   pair<int, int> move;
   NodeWithMove() {}
   NodeWithMove(pair<int, int> p, Node *n) : move(p), node(n) {}
};

NodeWithMove expand(Node *node, vector<pair<int, int>> &moves, UltimateTicTacToe &game, int player)
{
   node->last_expanded++;
   pair<int, int> move = node->validmoves[node->last_expanded];

   int res = game.move(move.first, move.second, player, moves);
   updateActions(moves, move);

   node->sons[node->last_expanded] = new Node(moves, game, node, node->validmoves[node->last_expanded]);

   if (res != -1)
      node->sons[node->last_expanded]->terminal = res;

   return NodeWithMove(node->validmoves[node->last_expanded], node->sons[node->last_expanded]);
}

NodeWithMove bestChild(Node *node, int currentPlayer, UltimateTicTacToe &game, vector<pair<int, int>> &validMoves)
{
   Node *chosenSon;
   pair<int, int> move;
   double bestScore = -1.0;
   for (auto son : node->sons)
   {
      double score = (double)(son.second->wins[currentPlayer] / (double)son.second->simulations) + 1.4 * sqrt((2.0 * log(node->simulations) / son.second->simulations));
      double K = 1000;
      double beta = sqrt(K / (3.0 * (double)(node->simulations) + K));
      string mv = to_string(node->validmoves[son.first].first) + to_string(node->validmoves[son.first].second);

      double raveScore = (double)(1.0 - beta) * (score) + (double)(beta * (double)son.second->amafWins[mv] / (double)son.second->amafSimulations);
      if (raveScore > bestScore)
      {
         chosenSon = son.second;
         bestScore = raveScore;
         move = node->validmoves[son.first];
      }
   }
   game.move(move.first, move.second, currentPlayer, validMoves);
   // cerr << "deleting3: " << move.first << " " << move.second << endl;
   updateActions(validMoves, move);
   return NodeWithMove(move, chosenSon);
}

NodeWithMove treePolicy(Node *node, int currentPlayer, vector<pair<int, int>> &validMoves, UltimateTicTacToe &game)
{
   NodeWithMove response;
   while (node->terminal == -1)
   {
      if (node->last_expanded < (int)(node->validmoves.size() - 1))
      {
         // cerr << "returning in expand" << endl;
         return expand(node, validMoves, game, currentPlayer);
      }
      else
      {
         response = bestChild(node, currentPlayer, game, validMoves);
         usedMoves.push_back(to_string(response.move.first) + to_string(response.move.second));
      }

      node = response.node;
      currentPlayer = 1 - currentPlayer;
   }
   // cerr << "terminal: " << node->terminal << endl;
   return response;
}

void backPropagate(Node *current, int player, int res)
{
   while (current)
   {
      current->simulations++;
      current->wins[player] += res;
      current = current->parent;
   }
}

void MCTS(UltimateTicTacToe &game, Node *root, int currentPlayer, vector<pair<int, int>> validMoves, chrono::steady_clock::time_point time_start)
{
   while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() < TIME_THRESHOLD)
   {
      UltimateTicTacToe gameCopy(game);
      vector<pair<int, int>> movesCopy = validMoves;

      NodeWithMove simulationNodeWithMove = treePolicy(root, currentPlayer, movesCopy, gameCopy);
      Node *simulationNode = simulationNodeWithMove.node;
      pair<int, int> move = simulationNodeWithMove.move;

      // cerr << "simulation start" << endl;
      int res;
      if (simulationNode->terminal != -1)
         res = simulationNode->terminal == currentPlayer ? 1 : -1;
      else
         res = simulateGame(gameCopy, movesCopy, move, currentPlayer, time_start);

      updateAmaf(simulationNode, (res == currentPlayer));
      usedMoves.resize(0);

      if (res == -1)
         res = 0;

      backPropagate(simulationNode, currentPlayer, res);
   }
}

vector<pair<int, int>> getAllActions()
{
   vector<pair<int, int>> res;
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         res.push_back(make_pair(i, j));
      }
   }
   return res;
}

int main()
{
   srand(time(NULL));

   int opponent = 0, me = 1, currentPlayer = 0, turn = 1;

   UltimateTicTacToe game;

   Node *root = nullptr;
   vector<pair<int, int>> validActions;
   TIME_THRESHOLD = FIRST_ROUND;
   // game loop
   while (1)
   {
      int opponentRow;
      int opponentCol;
      cin >> opponentRow >> opponentCol;
      cin.ignore();
      int validActionCount;
      cin >> validActionCount;
      cin.ignore();
      chrono::steady_clock::time_point begin = chrono::steady_clock::now();

      for (int i = 0; i < validActionCount; i++)
      {
         int row, col;
         cin >> row >> col;
         cin.ignore();
         if (turn == 1)
            validActions.push_back({row, col});
      }

      if (opponentRow == -1)
      {
         opponent = 1;
         me = 0;
      }
      else
      {
         if (turn == 1)
         { // TO DO: double check if that's supposed to be here
            validActions = getAllActions();
         }

         game.move(opponentRow, opponentCol, opponent, validActions); // possible moves before opponent move

         // cerr << "deleting4: " << opponentRow << " " << opponentCol << endl;
         updateActions(validActions, make_pair(opponentRow, opponentCol));

         if (root == nullptr)
            root = new Node(validActions, game, nullptr, {opponentRow, opponentCol});

         for (int i = 0; i < root->validmoves.size(); i++)
         {
            if (root->validmoves[i] == make_pair(opponentRow, opponentCol))
            {
               if (root->sons.find(i) == root->sons.end())
                  root->sons[i] = new Node(validActions, game, root, make_pair(opponentRow, opponentCol));
               root = root->sons[i];
            }
         }
      }
      if (root == nullptr)
         root = new Node(validActions, game, nullptr, {opponentRow, opponentCol});

      pair<int, int> move;
      Node *chosenChild;
      double bestScore = -1.0;

      int sim = root->simulations;
      MCTS(game, root, me, validActions, begin);
      cerr << "simulations: " << root->simulations - sim << endl;

      for (auto son : root->sons)
      {
         double score = son.second->simulations == 0 ? 0.0 : (double)(son.second->wins[me] / (double)son.second->simulations);

         if (score > bestScore)
         {
            move = root->validmoves[son.first];
            bestScore = score;
            chosenChild = son.second;
         }
      }

      cout << move.first << " " << move.second << endl;
      game.move(move.first, move.second, me, validActions);

      updateActions(validActions, move);

      root = chosenChild;
      turn++;
      TIME_THRESHOLD = ROUND_TIME;
   }
}