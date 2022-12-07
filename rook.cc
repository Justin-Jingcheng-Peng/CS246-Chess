#include "rook.h"
#include <algorithm>
#include <cmath>
#include "chessBoard.h"

Rook::Rook(char symbol): Piece{symbol} {}
bool Rook::valid_move(ChessBoard* bo, Position pos1, Position pos2){
  std::vector<std::vector<std::shared_ptr<Piece>>> board = bo->get_board();
  if ((pos1.get_x_pos() == pos2.get_x_pos() || pos1.get_y_pos() == pos2.get_y_pos()) &&
              (board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr ||
               board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != get_color())) {
                if (pos1.get_x_pos() == pos2.get_x_pos()) {
			for (int i = min(pos1.get_y_pos(), pos2.get_y_pos()) + 1; 
					i < max(pos1.get_y_pos(), pos2.get_y_pos()); ++i) {
				if (board[i][pos1.get_x_pos()] != nullptr) {
					return false;
				}
			}
		}
		else {
			for (int i = min(pos1.get_x_pos(), pos2.get_x_pos()) + 1;
                                        i < max(pos1.get_x_pos(), pos2.get_x_pos()); ++i) {
                                if (board[pos1.get_y_pos()][i] != nullptr) {
                                        return false;
                                }
                        }
		}
		return true;
        }
        else {
                return false;
        }
}
