#include <iostream>
#include "chessBoard.h"
#include "piece.h"
#include "pawn.h"
int main()
{
  ChessBoard chessBoard = ChessBoard{};
  while (true)
  {
    cout << "-------------a new move-------------" << endl;
    cout << chessBoard.round << "\'s round" << endl;
    char cmd;
    cin >> cmd;
    if (cmd == 'q')
    {
      break;
    }
    if (cmd == 'r')
    {
      chessBoard.undo();
      chessBoard.printBoardWithXYCordinates();
      continue;
    }
    if (cmd == 'c')
    {
      char direction;
      char color;
      cin >> direction;
      cin >> color;
      chessBoard.castlingMove(direction, color);
      chessBoard.printBoardWithXYCordinates();
      continue;
    }
    if (cmd == 'e')
    {
      int init_x, init_y, fin_x, fin_y, eaten_x, eaten_y;
      cin >> init_x >> init_y >> fin_x >> fin_y >> eaten_x >> eaten_y;
      chessBoard.enpassantMove(Position{init_x, init_y}, Position{fin_x, fin_y}, Position{eaten_x, eaten_y});
      chessBoard.printBoardWithXYCordinates();
      continue;
    }
    if (cmd == 'p')
    {
      int init_x, init_y, fin_x, fin_y;
      char pieceTurnedTo;
      cin >> init_x >> init_y >> fin_x >> fin_y >> pieceTurnedTo;
      chessBoard.promotionMove(Position{init_x, init_y}, Position{fin_x, fin_y}, pieceTurnedTo);
      chessBoard.printBoardWithXYCordinates();
      continue;
    }

    int init_x, init_y, fin_x, fin_y;
    cin >> init_x >> init_y >> fin_x >> fin_y;
    chessBoard.standardMove(Position{init_x, init_y}, Position{fin_x, fin_y});
    chessBoard.printBoardWithXYCordinates();
    if (chessBoard.isBlackBeingChecked() == true)
    {
      cout << "Black is being checked" << endl;
    }
    if (chessBoard.isWhiteBeingChecked() == true)
    {
      cout << "White is being checked" << endl;
    }
    if (chessBoard.isBlackLost() == true)
    {
      cout << "black lost, game over!" << endl;
      break;
    }
  }
  return 0;
}