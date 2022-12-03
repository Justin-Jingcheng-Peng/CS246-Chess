#include "move.h"

Move::Move(Piece *removed_piece, Position original_pos, Position final_pos, bool is_castling, bool is_enpassant, bool is_promotion) : removed_piece{removed_piece}, original_pos{original_pos}, final_pos{final_pos}, is_castling{is_castling}, is_enpassant{is_enpassant}, is_promotion{is_promotion} {}

Piece *Move::get_removed_piece() { return this->removed_piece; }

Position Move::get_orig_pos() { return this->original_pos; }

Position Move::get_final_pos() { return this->final_pos; }
