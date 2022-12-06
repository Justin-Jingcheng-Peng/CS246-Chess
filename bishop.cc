#include "bishop.h"
#include "chessBoard.h"

Bishop::Bishop(char symbol): Piece{symbol} {}

bool Bishop::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  std::vector<std::vector<std::shared_ptr<Piece>>> board = bo->get_board();
  int dist_row = abs(pos1.get_y_pos() - pos2.get_y_pos());
  int dist_col = abs(pos1.get_x_pos() - pos2.get_x_pos());
  if (dist_row == dist_col && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {return true;}
  if (dist_row == dist_col && board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != this->get_color()) {return true;}
  return false;
}
