#include "queen.h"
#include "chessBoard.h"
#include "move.h"
Queen::Queen(char symbol): Piece{symbol} {}
bool Queen::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  // To be implemented...
  return true;
}
void Queen::add_move_count() {
  this->move_count += 1;
}