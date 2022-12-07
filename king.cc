#include "king.h"
#include "chessBoard.h"
#include "move.h"

using namespace std;

King::King(char symbol): Piece{symbol} {}

bool King::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  vector<vector<shared_ptr<Piece>>> board = bo->get_board();
  if (board[pos2.get_y_pos()][pos2.get_x_pos()] != nullptr && board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() == this->get_color()) {return false;}
  char op_king = (this->get_color() == 'w' ? 'k' : 'K');
  Position op_king_pos = bo->get_piece_pos(op_king);
  if (pos2.dist_squared(op_king_pos) <= 2) {return false;}
  if (pos1.get_x_pos() == 4 && pos1.get_y_pos() == 7 && board[7][4]->get_move_count() == 0 && board[7][5] == nullptr && board[7][6] == nullptr && board[7][7] != nullptr && pos2.get_x_pos() == 6 && pos2.get_y_pos() == 7 && board[7][7]->get_symbol() == 'R' && board[7][7]->get_move_count() == 0 && !bo->is_position_check(Position(4,7), 'w') && !bo->is_position_check(Position(5,7), 'w') && !bo->is_position_check(Position(6,7), 'w')) {return true;}
  if (pos1.get_x_pos() == 4 && pos1.get_y_pos() == 7 && board[7][4]->get_move_count() == 0 && board[7][3] == nullptr && board[7][2] == nullptr && board[7][0] != nullptr && pos2.get_x_pos() == 2 && pos2.get_y_pos() == 7 && board[7][0]->get_symbol() == 'R' && board[7][0]->get_move_count() == 0 && !bo->is_position_check(Position(4,7), 'w') && !bo->is_position_check(Position(3,7), 'w') && !bo->is_position_check(Position(2,7), 'w')) {return true;}
  if (pos1.get_x_pos() == 4 && pos1.get_y_pos() == 0 && board[0][4]->get_move_count() == 0 && board[0][5] == nullptr && board[0][6] == nullptr && board[0][7] != nullptr && pos2.get_x_pos() == 6 && pos2.get_y_pos() == 0 && board[0][7]->get_symbol() == 'r' && board[0][7]->get_move_count() == 0 && !bo->is_position_check(Position(4,0), 'b') && !bo->is_position_check(Position(5,0), 'b') && !bo->is_position_check(Position(6,0), 'b')) {return true;}

  if (pos1.get_x_pos() == 4 && pos1.get_y_pos() == 0 && board[0][4]->get_move_count() == 0 && board[0][3] == nullptr && board[0][2] == nullptr && board[0][0] != nullptr && pos2.get_x_pos() == 2 && pos2.get_y_pos() == 0 && board[0][0]->get_symbol() == 'R' && board[0][0]->get_move_count() == 0 && !bo->is_position_check(Position(4,0), 'b') && !bo->is_position_check(Position(3,0), 'b') && !bo->is_position_check(Position(2,0), 'b')) {return true;}
  if (pos1.dist_squared(pos2) > 2 || bo->is_position_check(pos2, board[pos1.get_y_pos()][pos1.get_x_pos()]->get_color())) {return false;}
  
  return true;
}
