#include "pawn.h"
#include "chessBoard.h"
#include "move.h"

Pawn::Pawn(char symbol) : Piece{symbol} {}

bool Pawn::valid_move(ChessBoard* bo, Position pos1, Position pos2) {
  vector<vector<shared_ptr<Piece>>> board = bo->get_board();
	int step = ((get_color() == 'w') ? -1 : 1);
        if (pos2.get_x_pos() == pos1.get_x_pos() && pos2.get_y_pos() == pos1.get_y_pos() + step 
			&& board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {
		return true;
	}
	if (pos2.get_x_pos() == pos1.get_x_pos() && pos2.get_y_pos() == pos1.get_y_pos() + step * 2
                        && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr
			&& board[pos2.get_y_pos() - step][pos2.get_x_pos()] == nullptr
			&& get_move_count() == 0
			&& ((step == -1 && pos1.get_y_pos() == 6) || (step == 1 && pos1.get_y_pos() == 1))) {
                return true;
        }
	if (abs(pos2.get_x_pos() - pos1.get_x_pos()) == 1 && pos2.get_y_pos() - pos1.get_y_pos() == step &&
			board[pos2.get_y_pos()][pos2.get_x_pos()] != nullptr &&
			board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() != get_color()) {
		return true;
	}
	// en passant
	if (bo->get_num_moves() == 0) {
		return false;
	}
	Move last_move = bo->get_last_move();
        if (last_move.get_piece()->get_type() == 'p' &&
                        last_move.get_orig_pos().dist_squared(last_move.get_final_pos()) == 4 &&
                        last_move.get_piece()->get_color() != board[pos1.get_y_pos()][pos1.get_x_pos()]->get_color() &&
                        pos2.get_x_pos() == last_move.get_final_pos().get_x_pos() && (pos2.get_y_pos() == last_move.get_final_pos().get_y_pos() + step) &&
                        (abs(pos2.get_x_pos() - pos1.get_x_pos()) == 1) && (pos2.get_y_pos() - pos1.get_y_pos() == step)) {
        	return true;
	}
	return false;
}
