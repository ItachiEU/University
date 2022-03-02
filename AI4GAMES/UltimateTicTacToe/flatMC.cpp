#include <bits/stdc++.h>

using namespace std;

const int row1 = 7, row2 = 56, row3 = 448;
const int col1 = 292, col2 = 146, col3 = 73;
const int diag1 = 273, diag2 = 84;

double TIME_THRESHOLD = 95.0; //miliseconds

class UltimateTicTacToe
{
private:
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

public:
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

   int moveSmall(int row, int col, int player)
   {
      int smallRow = row % 3, smallCol = col % 3;
      int shift = (1 << (3 * smallRow + smallCol));
      auto oldState = board[row / 3][col / 3];
      board[row / 3][col / 3] = {player != 0 ? oldState.first : (oldState.first | shift), player != 1 ? oldState.second : (oldState.second | shift)};
      return smallGameEnd(board[row / 3][col / 3], player);
   }

   int getPossibleMovesCount(int row, int col)
   {
      int result = 9;
      for (int i = 0; i < 9; i++)
         result -= ((board[row][col].first & (1 << i)) or (board[row][col].second & (1 << i)));

      return result;
   }

   int move(int row, int col, int player, int moveCount, bool debug = false)
   {
      int boardRow = row / 3, boardCol = col / 3;
      int smallRow = row % 3, smallCol = col % 3;

      int response = moveSmall(row, col, player);

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
      return gameEnd(moveCount);
   }
};

vector<pair<int, int>> updateActions(vector<pair<int, int>> actions, pair<int, int> move)
{
   vector<pair<int, int>> temp;
   for (auto mv : actions)
   {
      if (mv != move)
         temp.push_back(mv);
   }
   return temp;
}

int simulateGame(UltimateTicTacToe &game, vector<pair<int, int>> validActions, pair<int, int> firstMove, int me, chrono::steady_clock::time_point time_start)
{
   int player = me;
   int result = game.move(firstMove.first, firstMove.second, player, validActions.size());

   pair<int, int> lastMove = firstMove;

   if (result != -1)
      return result == me ? 1 : -1;

   validActions = updateActions(validActions, firstMove);

   while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() < TIME_THRESHOLD)
   {
      player = 1 - player;
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

      pair<int, int> move = validActionsSmall[rand() % validActionsSmall.size()];
      result = game.move(move.first, move.second, player, validActions.size());
      if (result != -1)
         return result == me ? 1 : -1;
      validActions = updateActions(validActions, move);
      lastMove = move;
   }
   return 0;
}

pair<int, int> flatMC(UltimateTicTacToe &game, int me, vector<pair<int, int>> validActions, int opponentRow, int opponentCol, chrono::steady_clock::time_point time_start)
{
   int opponentRowSmall = opponentRow % 3, opponentColSmall = opponentCol % 3;
   vector<pair<int, int>> validActionsSmall;

   if (opponentRow != -1 and game.getPossibleMovesCount(opponentRowSmall, opponentColSmall) > 0)
   { // get moves limited to the small board forced by opponent
      for (auto mv : validActions)
      {
         if (mv.first / 3 == opponentRowSmall and mv.second / 3 == opponentColSmall)
            validActionsSmall.push_back(mv);
      }
   }
   if (validActionsSmall.size() == 0)
      validActionsSmall = validActions;

   vector<pair<int, int>> score(validActionsSmall.size(), {0, 0}); //{score, count}

   while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - time_start).count() < TIME_THRESHOLD)
   {
      int moveIndex = rand() % validActionsSmall.size();
      pair<int, int> move = validActionsSmall[moveIndex];

      UltimateTicTacToe gameCopy(game);
      int result = simulateGame(gameCopy, validActions, move, me, time_start);

      score[moveIndex] = {score[moveIndex].first + result,
                          score[moveIndex].second + 1};
   }

   double bestScore = -10000.0;
   int bestIndex = 0, simulations = 0, biggestCount = 0;
   for (int i = 0; i < score.size(); i++)
   {
      simulations += score[i].second;
      // cerr << score[i].first << " " << score[i].second << endl;
      if (score[i].second > 0 and ((double)(score[i].first / (double)score[i].second) > bestScore or ((double)(score[i].first / (double)score[i].second) == bestScore and score[i].second > biggestCount)))
      {
         bestScore = (double)(score[i].first / (double)score[i].second);
         bestIndex = i;
         biggestCount = score[i].second;
      }
   }
   //cerr <<"score: " << bestScore << " " << biggestCount << " " << endl;
   return validActionsSmall[bestIndex];
}

int main()
{
   srand(time(NULL));

   int opponent = 0, me = 1, currentPlayer = 0;

   UltimateTicTacToe game;
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

      if (opponentRow == -1)
      {
         opponent = 1;
         me = 0;
      }
      else
      {
         game.move(opponentRow, opponentCol, opponent, validActionCount + 1); // possible moves before opponent move
      }

      vector<pair<int, int>> validActions;
      for (int i = 0; i < validActionCount; i++)
      {
         int row, col;
         cin >> row >> col;
         cin.ignore();
         validActions.push_back({row, col});
      }
      pair<int, int> move;

      move = flatMC(game, me, validActions, opponentRow, opponentCol, begin);

      cout << move.first << " " << move.second << endl;
      game.move(move.first, move.second, me, validActionCount);
   }
}