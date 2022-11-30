#include "pawn.h"
#include "chessBoard.h"
#include "move.h"

Pawn::Pawn(char symbol): Piece{symbol} {}

bool Pawn::valid_move(ChessBoard* bo, Position pos1, Position pos2) {
  std::vector<std::vector<Piece*>> board = bo->get_board();
  // int step = ((this->get_color() == 'w') ? -1 : 1);
  int dist_row = abs(pos1.get_y_pos() - pos2.get_y_pos());
  int dist_col = abs(pos1.get_x_pos() - pos2.get_x_pos());
  if (dist_row == 1 && pos1.get_x_pos() == pos2.get_x_pos() && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {return true;}
  if(this->move_count == 0) {
    if (dist_row == 2 && pos1.get_x_pos() == pos2.get_x_pos() && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {return true;}
  }
  // Checks for possible diagonal attack
  if (dist_col == 1 && dist_row == 1 && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {return false;} 
  else if (dist_col == 1 && dist_row == 1 && board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != this->get_color()) {return true;}
  // Check for en passant
  if (bo->get_num_moves() == 0) {
    return false;
  }
  // Move recent_move = bo->get_last_move();
  // Piece* moved_piece = recent_move.get_moved_piece();
  // Conditions for en passant
  // int moved_dist_row = abs(recent_move.get_orig_pos().get_y_pos() - recent_move.get_final_pos().get_y_pos());
  // int moved_dist_col = abs(recent_move.get_orig_pos().get_x_pos() - recent_move.get_final_pos().get_x_pos());
  // if (moved_piece->get_type() == 'p' && moved_dist_col == 0 && moved_dist_row == 2 && moved_piece->get_color() != this->get_color() && pos2.get_x_pos() == recent_move.get_final_pos().get_x_pos() && abs(pos2.get_final_y_pos() - recent_move.get_final_pos().get_y_pos()) == 1 && dist_row == 1 && dist_col == 1) {return true;}
  // return false;
}


void Pawn::add_move_count() {
  this->move_count += 1;
}

