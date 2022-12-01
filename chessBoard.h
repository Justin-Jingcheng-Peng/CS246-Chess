#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_
#include "bishop.h"
#include "king.h"
#include "move.h"
#include "pawn.h"
#include "piece.h"
#include "position.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
// #include "subject.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ChessBoard
{
public:
  char round;
  ChessBoard();
  ~ChessBoard();

  vector<Move> pastMoves;
  vector<vector<Piece *>> board;

  vector<vector<Piece *>> get_board();
  Piece *getPieceAt(int x, int y);
  Move get_last_move(); // returns the most recent move

  bool isInBound(Position p1);
  bool isInBoundAndNonNull(Position p1);
  bool isBlackBeingChecked();
  void move(Position initPos, Position finalPos);
  void printBoard();
  void setNewPiece(int x, int y, char symbol);
  int isGameFinish();
  int getLastMove();
  int get_num_moves();
};

#endif