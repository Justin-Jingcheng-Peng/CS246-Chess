#include <iostream>
#include "chessBoard.h"
#include "piece.h"
#include "pawn.h"
int main()
{
  ChessBoard chessBoard = ChessBoard{};

  chessBoard.move(Position{7, 1}, Position{1, 6});
  chessBoard.move(Position{0, 4}, Position{3, 4});
  cout << chessBoard.isBlackBeingChecked() << endl;
  chessBoard.printBoard();
}