#include "move.h"

using namespace std;

Move::Move(shared_ptr<Piece> piece, shared_ptr<Piece> removed_piece, Position original_pos, Position final_pos, bool is_castling, bool is_enpassant, bool is_promotion) : piece{piece}, removed_piece{removed_piece}, original_pos{original_pos}, final_pos{final_pos}, is_castling{is_castling}, is_enpassant{is_enpassant}, is_promotion{is_promotion} {}

shared_ptr<Piece> Move::get_piece() {return this->piece;}

shared_ptr<Piece> Move::get_removed_piece() { return this->removed_piece; }

Position Move::get_orig_pos() { return this->original_pos; }

Position Move::get_final_pos() { return this->final_pos; }

bool Move::get_enpassant() {return this->is_enpassant;}

bool Move::get_castling() {return this->is_castling;}

bool Move::get_promotion() {return this->is_promotion;}

void Move::set_promotion(bool new_promote) {this->is_promotion = new_promote;}
