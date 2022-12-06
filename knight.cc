#include "knight.h"
#include "chessBoard.h"

Knight::Knight(char symbol): Piece{symbol} {}

bool Knight::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  std::vector<std::vector<std::shared_ptr<Piece>>> board = bo->get_board();
  int dist_row = abs(pos1.get_y_pos() - pos2.get_y_pos());
  int dist_col = abs(pos1.get_x_pos() - pos2.get_x_pos());
  if (dist_row == 2 && dist_col == 1 && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {return true;}
  if (dist_row == 2 && dist_col == 1 && board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != this->get_color()) {return true;}
  if (dist_row == 1 && dist_col == 2 && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {return true;}
  if (dist_row == 1 && dist_col == 2 && board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != this->get_color()) {return true;}
  return false;
}
