#include "bishop.h"
#include "chessBoard.h"
#include "move.h"
Bishop::Bishop(char symbol): Piece{symbol} {}
bool Bishop::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  // To be implemented...
  return true;
}
void Bishop::add_move_count() {
  this->move_count += 1;
}