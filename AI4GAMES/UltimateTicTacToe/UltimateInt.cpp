#include <bits/stdc++.h>

using namespace std;

class UltimateTicTacToe
{
private:
   vector<unordered_set<int>> rows, columns, diagonals;
   unordered_map<int, int> rowsCount, columnsCount, diagonalsCount;
   vector<vector<TicTacToe *>> board;
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

      if (!moveCount)
         return TicTacToeWins[0] > TicTacToeWins[1] ? 0 : 1;

      return -1;
   }

public:
   UltimateTicTacToe()
   {
      rows.resize(3);
      columns.resize(3);
      diagonals.resize(2);
      board = vector<vector<TicTacToe *>>(3, vector<TicTacToe *>(3));
      for (int i = 0; i < 3; i++)
         for (int j = 0; j < 3; j++)
            board[i][j] = new TicTacToe();

      TicTacToeWins.resize(2, 0);
   }

   UltimateTicTacToe(UltimateTicTacToe &toCopy)
   {
      cerr << "in copy " << endl;
      rows = toCopy.rows;
      columns = toCopy.columns;
      diagonals = toCopy.diagonals;
      rowsCount = toCopy.rowsCount;
      columnsCount = toCopy.columnsCount;
      diagonalsCount = toCopy.diagonalsCount;
      for (int i = 0; i < 3; i++)
         for (int j = 0; j < 3; j++)
         {
            cerr << toCopy.getBoard(i, j)->getPossibleMovesCount() << endl;
            board[i][j] = new TicTacToe(*toCopy.getBoard(i, j));
            cerr << board[i][j]->getPossibleMovesCount() << endl;
         }
      cerr << " copied board" << endl;
      TicTacToeWins = toCopy.TicTacToeWins;
   }

   int move(int row, int col, int player, int moveCount)
   {
      int boardRow = row / 3, boardCol = col / 3;
      int smallRow = row % 3, smallCol = col % 3;

      cerr << boardRow << " " << boardCol << endl;

      int response = board[boardRow][boardCol]->move(smallRow, smallCol, player);

      cerr << "response: " << response << endl;

      if (response != -1)
         TicTacToeWins[response]++;

      if (response == player)
      {
         rows[boardRow].insert(player);
         columns[boardCol].insert(player);
         if (boardRow == boardCol)
         {
            diagonals[0].insert(player);
            diagonalsCount[0]++;
         }
         if (boardRow == abs(2 - boardCol))
         {
            diagonals[1].insert(player);
            diagonalsCount[1]++;
         }
      }
      return gameEnd(moveCount);
   }

   TicTacToe *getBoard(int row, int col)
   {
      return board[row][col];
   }
};

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
      int opponentRowSmall = opponentRow % 3, opponentColSmall = opponentCol % 3;

      vector<pair<int, int>> validActionsSmall;
      if (opponentRow != -1 and game.getBoard(opponentRowSmall, opponentColSmall)->getPossibleMovesCount() > 0)
      { // get moves limited to the small board forced by opponent
         for (auto mv : validActions)
         {
            if (mv.first / 3 == opponentRowSmall and mv.second / 3 == opponentColSmall)
               validActionsSmall.push_back(mv);
         }
      }

      bool canWin = false;
      pair<int, int> move;

      if (validActionsSmall.size() == 0)
         validActionsSmall = validActions;

      for (auto mv : validActionsSmall)
      {
         UltimateTicTacToe gameCopy(game);
         int test = gameCopy.move(mv.first, mv.second, me, validActionCount);
         cerr << test << endl;
         if (test == me)
         {
            cout << mv.first << " " << mv.second << endl;
            canWin = true;
            move = mv;
            break;
         }
      }
      if (!canWin)
      {
         move = validActions[rand() % validActionCount];
         cout << move.first << " " << move.second << endl;
      }
      game.move(move.first, move.second, me, validActionCount);
   }
}