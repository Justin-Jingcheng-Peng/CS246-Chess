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
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Error
{
private:
  string errorMessage;
public:
  Error(string errorMessage) : errorMessage{errorMessage} {}
  string get_error_message() {
    return errorMessage;
  }
}

class ChessBoard
{
private:
  void move(Position initPos, Position finalPos, bool is_castling);

public:
  char round;
  vector<Move> pastMoves;
  vector<vector<Piece *>> board;

  ChessBoard();
  ~ChessBoard();

  vector<vector<Piece *>> get_board();
  Piece *getPieceAt(int x, int y);
  Move get_last_move();
  

  bool isInBound(Position p1);
  bool isInBoundAndNonNull(Position p1);
  bool isBlackBeingChecked();
  bool isWhiteBeingChecked();
  bool isBlackLost();
  bool isWhiteLost();

  void undo();
  void standardMove(Position initPos, Position finalPos);
  void castlingMove(char direction, char color);
  void enpassantMove(Position initPos, Position finalPos, Position eatenPiecePosition);
  void promotionMove(Position initPos, Position finalPos, char pieceTurnedTo);
  void printBoardWithXYCordinates();
  void printBoardWithStandardCordinates();
  void setNewPiece(int x, int y, char symbol);
  bool isGameFinish();
};

#endif