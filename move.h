#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "position.h"

class Piece;

class Move
{
public:
  Piece *removed_piece;  // The piece that was removed
  Position original_pos; // The position of the moved_piece before being moved.
  Position final_pos;    // The position of the moved_piece after moving
  bool is_castling;      // Determine if this move is the "LAST" move of a castling move. We consider castling as two individual moves.
  bool is_enpassant;
  bool is_promotion;

  // Ctor for Move
  Move(Piece *removed_piece, Position original_pos, Position final_pos, bool is_castling, bool is_empassant, bool is_promotion);

  // getter for removed_piece field
  Piece *get_removed_piece();
  // getter for original_pos field
  Position get_orig_pos();
  // getter for final_pos field
  Position get_final_pos();
};

#endif
