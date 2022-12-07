#include "bishop.h"
#include "chessBoard.h"

Bishop::Bishop(char symbol): Piece{symbol} {}

bool Bishop::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  std::vector<std::vector<std::shared_ptr<Piece>>> board = bo->get_board();
  if (abs(pos1.get_y_pos() - pos2.get_y_pos()) == abs(pos1.get_x_pos()-pos2.get_x_pos()) && (board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr || board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != this->get_color())) {
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
  else {return false;}
}
