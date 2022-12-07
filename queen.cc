#include "queen.h"
#include <cmath>
#include "chessBoard.h"

Queen::Queen(char symbol): Piece{symbol} {}

bool Queen::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  std::vector<std::vector<std::shared_ptr<Piece>>> board = bo->get_board();
  if (abs(pos1.get_y_pos() - pos2.get_y_pos()) == abs(pos1.get_x_pos() - pos2.get_x_pos()) && (board[pos2.get_y_pos()][pos1.get_x_pos()] == nullptr || board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != this->get_color())) {
    return diagonal(board, pos1, pos2);
  }
  if ((pos1.get_x_pos() == pos2.get_x_pos() || pos1.get_y_pos() == pos1.get_y_pos()) && (board[pos2.get_y_pos()][pos1.get_x_pos()] == nullptr || board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != this->get_color())) {
    return straight(board, pos1, pos2);
  }
  return false;
}

bool Queen::diagonal(std::vector<std::vector<std::shared_ptr<Piece>>> board, Position pos1, Position pos2) {
  int move_x = 1; 
  int move_y = 1;
  if (pos2.get_y_pos() < pos1.get_y_pos()) {move_y = -1;}
  if (pos2.get_x_pos() < pos1.get_x_pos()) {move_x = -1;}
  int j = pos1.get_x_pos() + move_x;
  for (int i = pos1.get_y_pos() + move_y; i != pos2.get_y_pos(); i += move_y) {
    if (board[i][j] != nullptr) {return false;}
    j += move_x;
  }
  return true;
}

bool Queen::straight(std::vector<std::vector<std::shared_ptr<Piece>>> board, Position pos1, Position pos2) {
  if (pos1.get_x_pos() == pos2.get_x_pos()) {
    for (int i = min(pos1.get_y_pos(), pos2.get_y_pos()); i < max(pos1.get_y_pos(), pos2.get_y_pos()); ++i) {
      if (board[i][pos1.get_x_pos()] != nullptr) {return false;}
    }
  }
  else {
    for (int i = min(pos1.get_x_pos(), pos2.get_x_pos()); i < max(pos1.get_x_pos(), pos2.get_x_pos()); ++i) {
      if (board[pos1.get_y_pos()][i] != nullptr) {
        return false;
      }
    }
  }
  return true;
}
