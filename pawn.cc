#include "pawn.h"
#include "chessBoard.h"
#include "move.h"

Pawn::Pawn(char symbol) : Piece{symbol} {}

bool Pawn::valid_move(ChessBoard *bo, Position pos1, Position pos2)
{
  return true;
}

void Pawn::add_move_count()
{
  this->move_count += 1;
}
