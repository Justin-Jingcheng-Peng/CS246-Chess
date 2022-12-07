#include "knight.h"
#include "chessBoard.h"

Knight::Knight(char symbol): Piece{symbol} {}

bool Knight::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  std::vector<std::vector<std::shared_ptr<Piece>>> board = bo->get_board();
  if (pos1.dist_squared(pos2) == 5 && (board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr || board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != this->get_color())) {
    return true;
  }
  else {
    return false;
  }
}
