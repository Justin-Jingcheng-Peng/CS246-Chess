#include "move.h"

Move::Move(Piece* moved_piece, Piece* removed_piece, Position original_pos, Position final_pos, bool is_en_passant, bool is_castle, bool is_convert):moved_piece{moved_piece}, removed_piece{removed_piece}, original_pos{original_pos}, final_pos{final_pos}, is_en_passant{is_en_passant}, is_castle{is_castle}, is_convert{is_convert} {}

Piece* Move::get_moved_piece() {return this->moved_piece;}

Piece* Move::get_removed_piece() {return this->removed_piece;}

Position Move::get_orig_pos() {return this->original_pos;}

Position Move::get_final_pos() {return this->final_pos;}

bool Move::get_en_passant() {return this->is_en_passant;}

bool Move::get_castle() {return this->is_castle;}

bool Move::get_convert() {return this->is_convert;}

void Move::set_convert(bool new_convert) {this->is_convert = new_convert;}
