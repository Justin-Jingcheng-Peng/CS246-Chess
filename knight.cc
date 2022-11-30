#include "knight.h"
#include "chessBoard.h"
#include "move.h"
Knight::Knight(char symbol): Piece{symbol} {}
bool Knight::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  // To be implemented...
  return true;
}
void Knight::add_move_count() {
  this->move_count += 1;
}