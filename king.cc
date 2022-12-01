#include "king.h"
#include "chessBoard.h"
#include "move.h"
King::King(char symbol): Piece{symbol} {}
bool King::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  // To be implemented....
  return true;
}
void King::add_move_count() {
  this->move_count += 1;
}