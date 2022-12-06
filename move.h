#ifndef MOVE_H
#define MOVE_H
#include <string>
#include <memory>
#include "position.h"

class Piece;

class Move
{
private:
  std::shared_ptr<Piece> piece;
  std::shared_ptr<Piece> removed_piece;  // The piece that was removed
  Position original_pos; // The position of the moved_piece before being moved.
  Position final_pos;    // The position of the moved_piece after moving
  bool is_castling;      // Determine if this move is the "LAST" move of a castling move. We consider castling as two individual moves.
  bool is_enpassant;
  bool is_promotion;
public:
  // Ctor for Move
  Move(std::shared_ptr<Piece> piece, std::shared_ptr<Piece> removed_piece,Position original_pos, Position final_pos, bool is_castling, bool is_enpassant, bool is_promotion);
  // getter for piece field
  std::shared_ptr<Piece> get_piece();
  // getter for removed_piece field
  std::shared_ptr<Piece> get_removed_piece();
  // getter for original_pos field
  Position get_orig_pos();
  // getter for final_pos field
  Position get_final_pos();
  bool get_enpassant();
  bool get_castling();
  bool get_promotion();
  // setter for is_promotion field
  void set_promotion(bool new_promote);
};

#endif
