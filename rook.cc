#include "rook.h"
#include "chessBoard.h"

Rook::Rook(char symbol): Piece{symbol} {}
bool Rook::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  std::vector<std::vector<Piece*>> board = bo->get_board();
  int dist_row = abs(pos1.get_x_pos() - pos2.get_x_pos());
  int dist_col = abs(pos1.get_y_pos() - pos2.get_y_pos());
  if (dist_row == 0 && dist_col > 0 && board[pos2.get_x_pos()][pos2.get_y_pos()] == nullptr) {return true;}
  if (dist_row > 0 && dist_col == 0 && board[pos2.get_x_pos()][pos2.get_y_pos()] == nullptr) {return true;}
  if (dist_row > 0 && dist_col == 0 && board[pos2.get_x_pos()][pos2.get_y_pos()]->get_color() != this->get_color()) {return true;}
  if (dist_row == 0 && dist_col == 0 && board[pos2.get_x_pos()][pos2.get_y_pos()]->get_color() != this->get_color()) {return true;}
  return false;
}
