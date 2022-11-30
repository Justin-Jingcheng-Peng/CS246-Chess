#include "rook.h"
#include "chessBoard.h"
#include "move.h"
Rook::Rook(char symbol): Piece{symbol} {}
bool Rook::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  // To be implemented...
  return true;
}
void Rook::add_move_count() {
  this->move_count += 1;
}