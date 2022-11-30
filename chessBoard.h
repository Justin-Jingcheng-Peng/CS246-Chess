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

class ChessBoard {
public:
  ChessBoard();
  ~ChessBoard();
  vector<Move> pastMoves;
  vector<vector<Piece *>> board;
  void move(Position initPos, Position finalPos);
  Piece *getPieceAt(int x, int y);
  int isGameFinish();
  int getLastMove();
  void setup_addPiece(string newPieceName);
  void setup_removePiece(Position pos);
  vector<vector<Piece*>> get_board();
  int get_num_moves();
  Move get_last_move(); // returns the most recent move
  /*Testing functions*/
  void printBoard();
  void setNewPiece(int x, int y, char symbol);
};

#endif