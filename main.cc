#include <iostream>
#include "chessBoard.h"
#include "piece.h"
#include "pawn.h"
int main() {
  ChessBoard chessBoard = ChessBoard{};

  Position p1 = {0,0};
  Position p2 = {4,4};
  Position p3 = {6,4};
  chessBoard.move(p1,p3);
  
  
  
  chessBoard.printBoard();
}