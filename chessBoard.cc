#include "chessBoard.h"
#include <cmath>

using namespace std;

ChessBoard::ChessBoard() {
    score["White"] = 0;
    score["Black"] = 0;
    this->mode = "pre game";
    this->make_empty_board();
}

ChessBoard::~ChessBoard() {
    board.clear();
}

void ChessBoard::set_std_board() {
    // add black pieces
    this->setup_add_piece(make_shared<Rook>('r'), Position(0, 0));
    this->setup_add_piece(make_shared<Knight>('n'), Position(1,0));
    this->setup_add_piece(make_shared<Bishop>('b'), Position(2,0));
    this->setup_add_piece(make_shared<Queen>('q'), Position(3,0));
    this->setup_add_piece(make_shared<King>('k'), Position(4,0));
    this->setup_add_piece(make_shared<Bishop>('b'), Position(5,0));
    this->setup_add_piece(make_shared<Knight>('n'), Position(6,0));
    this->setup_add_piece(make_shared<Rook>('r'), Position(7,0));
    for (int i = 0; i < 8; ++i) {
        this->setup_add_piece(make_shared<Pawn>('p'), Position(i,1));
    }
    // add white pieces
    this->setup_add_piece(make_shared<Rook>('R'), Position(0, 7));
    this->setup_add_piece(make_shared<Knight>('N'), Position(1,7));
    this->setup_add_piece(make_shared<Bishop>('B'), Position(2,7));
    this->setup_add_piece(make_shared<Queen>('Q'), Position(3,7));
    this->setup_add_piece(make_shared<King>('K'), Position(4,7));
    this->setup_add_piece(make_shared<Bishop>('B'), Position(5,7));
    this->setup_add_piece(make_shared<Knight>('N'), Position(6,7));
    this->setup_add_piece(make_shared<Rook>('R'), Position(7,7));
    for (int i = 0; i < 8; ++i){
        this->setup_add_piece(make_shared<Pawn>('P'), Position(i,6));
    }
}

bool ChessBoard::is_empty_board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(board[i][j] != nullptr) {return false;}
        }
    }
    return true;
}

void ChessBoard::make_empty_board() {
    bool make_board = true;
    for (int i = 0; i < 8; ++i) {
        vector<shared_ptr<Piece>> row;
        for (int j = 0; j < 8; ++j) {
            row.emplace_back(nullptr);
            if (!make_board) {board[i][j] = nullptr;}
        }
        if (make_board) {board.emplace_back(row);}
    }
}

void ChessBoard::move_king(Position pos1, Position pos2) {
    if (!board[pos1.get_y_pos()][pos1.get_x_pos()]->valid_move(this, pos1, pos2)) {
        throw Error{"Invalid King or Castling move."};
    }
    int dist_row = abs(pos1.get_y_pos() - pos2.get_x_pos());
    int dist_col = abs(pos1.get_x_pos() - pos2.get_x_pos());
    if (dist_row == 1 && dist_col == 0) {
        pastMoves.emplace_back(board[pos1.get_y_pos()][pos1.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()], pos1, pos2, false, false, false);
        board[pos2.get_y_pos()][pos2.get_x_pos()] = board[pos1.get_y_pos()][pos1.get_x_pos()];
        board[pos1.get_y_pos()][pos1.get_x_pos()]->add_move_count();
        board[pos1.get_y_pos()][pos1.get_x_pos()] = nullptr;
    }
    else if (dist_row == 0 && dist_col == 1) {
        pastMoves.emplace_back(board[pos1.get_y_pos()][pos1.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()], pos1, pos2, false, false, false);
        board[pos2.get_y_pos()][pos2.get_x_pos()] = board[pos1.get_y_pos()][pos1.get_x_pos()];
        board[pos1.get_y_pos()][pos1.get_x_pos()]->add_move_count();
        board[pos1.get_y_pos()][pos1.get_x_pos()] = nullptr;
    }
    else if (dist_row == dist_col) {
        pastMoves.emplace_back(board[pos1.get_y_pos()][pos1.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()], pos1, pos2, false, false, false);
        board[pos2.get_y_pos()][pos2.get_x_pos()] = board[pos1.get_y_pos()][pos1.get_x_pos()];
        board[pos1.get_y_pos()][pos1.get_x_pos()]->add_move_count();
        board[pos1.get_y_pos()][pos1.get_x_pos()] = nullptr;
    }
    // Castling
    else if (pos2.get_x_pos() == 6 && pos2.get_y_pos() == 7) {
        castling_move(Position(4,7), Position(6,7), Position(7,7), Position(5,7));
    }
    else if (pos2.get_x_pos() == 2 && pos2.get_y_pos() == 7) {
        castling_move(Position(4,7), Position(2,7), Position(0,7), Position(3,7));
    }
    else if (pos2.get_x_pos() == 6 && pos2.get_y_pos() == 0) {
        castling_move(Position(4,0), Position(6,0), Position(7,0), Position(5,0));
    }
    else if (pos2.get_x_pos() == 2 && pos2.get_y_pos() == 0) {
        castling_move(Position(4,0), Position(2,0), Position(0,0), Position(3,0));
    }
}

bool ChessBoard::is_pos_in_check(Position pos, char colour) {
    // imagine it being filled with a piece.
    shared_ptr<Piece> temp = board[pos.get_y_pos()][pos.get_x_pos()];
    char queen = (colour == 'w' ? 'Q' : 'q');
    board[pos.get_y_pos()][pos.get_x_pos()] = make_shared<Queen>(queen);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((board[i][j] == nullptr) || (board[i][j]->get_color() == colour)) {continue;}
            if (board[i][j]->valid_move(this, Position(j,i), pos)) {
                board[pos.get_y_pos()][pos.get_x_pos()] = temp;
                return true;
            }
        }
    }

    board[pos.get_y_pos()][pos.get_x_pos()] = temp;
    return false;
}

bool ChessBoard::is_white_checked() {return is_pos_in_check(get_piece_pos('K'), 'w');}

bool ChessBoard::is_black_checked() {return is_pos_in_check(get_piece_pos('k'), 'b');}

bool ChessBoard::can_white_king_move(Position white_king_pos) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i != white_king_pos.get_y_pos() || j != white_king_pos.get_x_pos()) && board[white_king_pos.get_y_pos()][white_king_pos.get_x_pos()]->valid_move(this, white_king_pos, Position(j,i))) {
                return true;
            }
        }
    } 
    return false;
}

bool ChessBoard::can_black_king_move(Position black_king_pos) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i != black_king_pos.get_y_pos() || j != black_king_pos.get_x_pos()) && board[black_king_pos.get_y_pos()][black_king_pos.get_x_pos()]->valid_move(this, black_king_pos, Position(j,i))) {
                return true;
            }
        }
    } 
    return false;
}

void ChessBoard::castling_move(Position king_pos_1, Position king_pos_2, Position rook_pos_1, Position rook_pos_2) {
    pastMoves.emplace_back(board[king_pos_1.get_y_pos()][king_pos_1.get_x_pos()], nullptr, king_pos_1, king_pos_2, true, false, false);
    board[king_pos_2.get_y_pos()][king_pos_2.get_x_pos()] = board[king_pos_1.get_y_pos()][king_pos_1.get_x_pos()];
    board[king_pos_2.get_y_pos()][king_pos_2.get_x_pos()]->add_move_count();
    board[rook_pos_2.get_y_pos()][rook_pos_2.get_x_pos()] = board[rook_pos_1.get_y_pos()][rook_pos_1.get_x_pos()];
    board[rook_pos_2.get_y_pos()][rook_pos_2.get_x_pos()]->add_move_count();
    board[king_pos_1.get_y_pos()][king_pos_1.get_x_pos()] = nullptr;
    board[rook_pos_1.get_y_pos()][rook_pos_1.get_x_pos()] = nullptr;
}

void ChessBoard::move_pawn(Position pos1, Position pos2) {
    if (!board[pos1.get_y_pos()][pos1.get_x_pos()]->valid_move(this, pos1, pos2)) {
        throw Error{"Invalid pawn move."};
    }
    // En passant
    if (pos2.get_x_pos() != pos1.get_x_pos() && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {
        Move recent_move = this->get_last_move();
        pastMoves.emplace_back(board[pos1.get_y_pos()][pos1.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()], pos1, pos2, false, true, false);
        board[pos2.get_y_pos()][pos2.get_x_pos()] = board[pos1.get_y_pos()][pos1.get_x_pos()];
        board[pos1.get_y_pos()][pos1.get_x_pos()]->add_move_count();
        board[pos1.get_y_pos()][pos1.get_x_pos()] = nullptr;
        board[recent_move.get_final_pos().get_y_pos()][recent_move.get_final_pos().get_x_pos()] = nullptr;
    }
    else {
        pastMoves.emplace_back(board[pos1.get_y_pos()][pos1.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()], pos1, pos2, false, false, false);
        board[pos2.get_y_pos()][pos2.get_x_pos()] = board[pos1.get_y_pos()][pos1.get_x_pos()];
        board[pos1.get_y_pos()][pos1.get_x_pos()]->add_move_count();
        board[pos1.get_y_pos()][pos1.get_x_pos()] = nullptr;
    }

    // Promotion
    if ((board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() == 'w' && pos2.get_y_pos() == 0) || (board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() == 'b' && pos2.get_y_pos() == 7)) {
        if (board[pos2.get_y_pos()][pos2.get_x_pos()]->get_color() == 'w') {
            board[pos2.get_y_pos()][pos2.get_x_pos()] = make_shared<Queen>('Q');
            board[pos2.get_y_pos()][pos2.get_x_pos()]->add_move_count();
        }
        else {
            board[pos2.get_y_pos()][pos2.get_x_pos()] = make_shared<Queen>('q');
            board[pos2.get_y_pos()][pos2.get_x_pos()]->add_move_count();
        }
        pastMoves.back().set_promotion(true);
    }
}

void ChessBoard::move_promote(Position pos1, Position pos2, char promote) {
    if (board[pos1.get_y_pos()][pos1.get_x_pos()]->get_type() != 'p') {
        throw Error{"The piece at the given position is not a pawn."};
    }
    if (promote != 'r' && promote != 'R' && promote != 'B' && promote != 'b' && promote != 'N' && promote != 'n' && promote != 'Q' && promote != 'q') {
        throw Error{"You can only promote the pawn to either a bishop, rook, knight or queen."};
    }
    if (board[pos1.get_y_pos()][pos1.get_x_pos()]->valid_move(this, pos1, pos2) && ((board[pos1.get_y_pos()][pos1.get_x_pos()]->get_color() == 'w' && pos2.get_y_pos() == 0) || (board[pos1.get_y_pos()][pos1.get_x_pos()]->get_color() == 'b' && pos2.get_y_pos() == 7))) {
        promote_pawn(pos1, pos2, promote);
    } else {
        throw Error{"Invalid promotion."};
    }
    check_turn_switch();
}

void ChessBoard::promote_pawn(Position pos1, Position pos2, char promoted_to) {
    char colour = (promoted_to < 'a' ? 'w' : 'b');
    if (colour != board[pos1.get_y_pos()][pos1.get_x_pos()]->get_color()) {
        throw Error{"The colour of the promoted piece and the original piece do not match."};
    }
    pastMoves.emplace_back(board[pos1.get_y_pos()][pos1.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()], pos1, pos2, false, false, true);
    board[pos1.get_y_pos()][pos1.get_x_pos()] = nullptr;
    if (promoted_to == 'N' || promoted_to == 'n') {
        board[pos2.get_y_pos()][pos2.get_x_pos()] = make_shared<Knight>(promoted_to);
    } else if (promoted_to == 'B' || promoted_to == 'b') {
        board[pos2.get_y_pos()][pos2.get_x_pos()] = make_shared<Bishop>(promoted_to);
    } else if (promoted_to == 'R' || promoted_to == 'r') {
        board[pos2.get_y_pos()][pos2.get_x_pos()] = make_shared<Rook>(promoted_to);
    } else {
        board[pos2.get_y_pos()][pos2.get_x_pos()] = make_shared<Queen>(promoted_to);
    }
    board[pos2.get_y_pos()][pos2.get_x_pos()]->add_move_count();
}

bool ChessBoard::can_piece_block(Position pos) {
    if (board[pos.get_y_pos()][pos.get_x_pos()]->get_type() == 'n') {
        if (is_pos_in_check(pos, board[pos.get_y_pos()][pos.get_x_pos()]->get_color())) {
            return true;
        } else {return false;}
    }
    char king = 'k';
    if (board[pos.get_y_pos()][pos.get_x_pos()]->get_color() == 'b') {king = 'K';}
    Position opposite_king = this->get_piece_pos(king);
    int unit_x = 0;
    if (opposite_king.get_x_pos() - pos.get_x_pos() != 0) {
        unit_x = (opposite_king.get_x_pos() - pos.get_x_pos() > 0 ? 1 : -1);
    }
    int unit_y = 0;
    if (opposite_king.get_y_pos() - pos.get_y_pos() != 0) {
        unit_y = (opposite_king.get_y_pos() - pos.get_y_pos() > 0 ? 1 : -1);
    }
    int cur_x = pos.get_x_pos();
    int cur_y = pos.get_y_pos();
    while (cur_x != opposite_king.get_x_pos() || cur_y != opposite_king.get_y_pos()) {
        if (is_pos_in_check(Position(cur_x, cur_y), board[pos.get_y_pos()][pos.get_x_pos()]->get_color())) {return true;}
        cur_x += unit_x;
        cur_y += unit_y;
    }
    return false;
}

void ChessBoard::check_turn_switch(string msg) {
    string result = this->check_board();
    bool has_game_ended = false;
    if (result == "bc") {
        score["Black"] += 1;
        score[player[result[0]]] += 1;
        has_game_ended = true;
    }
    else if (result == "wc") {
        score["White"] += 1;
        score[player[result[0]]] += 1;
        has_game_ended = true;
    }
    else if (result == "s") {
        score["White"] += 0.5;
        score["Black"] += 0.5;
        score[player['w']] += 0.5;
        score[player['b']] += 0.5;
        has_game_ended = true;
    }
    else {this->turn_switch();}
    if (msg == "") {notifyObservers(result);}
    else {
        notifyObservers(msg + result);
    }
    if (has_game_ended) {
        this->clear_board();
    }
}

bool ChessBoard::is_stalemate(char colour) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((board[i][j] != nullptr) && (board[i][j]->get_color() == colour)) {
                for (int k = 0; k < 8; ++k) {
                    for (int l = 0; l < 8; ++l) {
                        if ((l != j || k != i) && board[i][j]->valid_move(this, Position(j,i), Position(l,k))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void ChessBoard::turn_switch() {
    if (this->turn == 'w') {this->turn = 'b';}
    else {this->turn = 'w';}
}

void ChessBoard::clear_board() {
    this->make_empty_board();
    this->pastMoves.clear();
    player.clear();
    this->turn = 'w';
    this->mode = "pre game";
}

vector<vector<shared_ptr<Piece>>> ChessBoard::get_board() {return this->board;}

void ChessBoard::set_mode(string mode) {this->mode = mode;}

string ChessBoard::get_mode() {return this->mode;}

Position ChessBoard::get_piece_pos(char piece) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->get_symbol() == piece) {
                return Position(j,i);
            }
        }
    }
    return Position(-1, -1);
}

Move ChessBoard::get_last_move() {return pastMoves.back();}

int ChessBoard::get_num_moves() {return pastMoves.size();}

char ChessBoard::get_turn() {return this->turn;}

map<string, int> ChessBoard::get_score() {return this->score;}

string ChessBoard::check_board() {
    if (this->count_pieces() == 2) { // Checks basic stalemate case
        return "stalemate";
    }
    bool white_checked = this->is_white_checked();
    bool black_checked = this->is_black_checked();
    bool white_stalemate = this->is_stalemate('w');
    bool black_stalemate = this->is_stalemate('b');
    // game can still be played "normal" state.
    if (!white_stalemate && !black_stalemate && !white_checked && !black_checked) {return "n";}
    // stalemate
    if ((white_stalemate || black_stalemate) && !white_checked && !black_checked) {return "s";}
    // Checks if any of the players ignored to get king out of check
    if ((this->turn == 'w' && white_checked) || (this->turn == 'b' && black_checked)) {
        this->undo();
        throw Error{"Invalid move. You are/will be in check!"};
    }
    Move recent_move = this->get_last_move();
    bool can_block = this->can_piece_block(recent_move.get_final_pos());
    Position white_king_pos = this->get_piece_pos('K');
    Position black_king_pos = this->get_piece_pos('k');
    bool white_king_move = this->can_white_king_move(white_king_pos);
    bool black_king_move = this->can_black_king_move(black_king_pos);
    // white checkmates black
    if (black_checked && !black_king_move && !can_block) {
        return "we";
    }
    // black checkmates white
    if (white_checked && !white_king_move && !can_block) {
        return "be";
    }
    // white checks black
    if (black_checked && (white_king_move || can_block)) {
        return "wc";
    }
    // black checks white
    if (white_checked && (black_king_move || can_block)) {
        return "bc";
    }
    // Otherwise, return that the game can still be played, in other words "normal" state.
    return "n";
}

void ChessBoard::start_game() {
    if (player.size() != 2) {
        throw Error{"Two players is required to play Chess."};
    }
    if (this->is_empty_board()) {
        this->set_std_board();
        this->turn = 'w';
    }
    if (turn != 'w' && turn != 'b') {turn = 'w';}
    this->mode = "in game";
    this->notifyObservers("normal");
}

void ChessBoard::add_player(string name, char colour) {
    this->player[colour] = name;
    if (name == "computer 1") {}
    else if (name == "computer 2") {}
    else if (name == "computer 3") {}
    else if (name == "computer 4") {}
}

void ChessBoard::setup_add_piece(shared_ptr<Piece> piece, Position pos) {
    board[pos.get_y_pos()][pos.get_x_pos()] = piece;
}

void ChessBoard::setup_remove_piece(Position pos) {
    board[pos.get_y_pos()][pos.get_x_pos()] = nullptr;
}

void ChessBoard::setup_set_turn(char colour) {
    this->turn = colour;
}

void ChessBoard::setup() {this->mode = "setup";}

void ChessBoard::setup_done() {
    Position white_king_pos = this->get_piece_pos('K');
    Position black_king_pos = this->get_piece_pos('k');
    if ((white_king_pos.get_x_pos() == -1 || white_king_pos.get_y_pos() == -1) || (black_king_pos.get_x_pos() == -1 || black_king_pos.get_y_pos() == -1)) {
        throw Error{"Both the white and the black kings must be present in the game."};
    }
    if (is_white_checked() || is_black_checked()) {
        throw Error{"Neither the black king nor the white king can be in check."};
    }
    for (int i = 0; i < 8; ++i) {
        if ((board[0][i] != nullptr && board[0][i]->get_type() == 'p') || (board[7][i] != nullptr && board[7][i]->get_type() == 'p')) {
            throw Error{"None of the pawns should be in the first or last rows."};
        }
    }
    int white_king_count = 0;
    int black_king_count = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->get_symbol() == 'K') {white_king_count += 1;}
            if (board[i][j] != nullptr && board[i][j]->get_symbol() == 'k') {black_king_count += 1;}
        }
    }
    if (white_king_count != 1 || black_king_count != 1) {
        throw Error{"There should be exactly one white king and black king!"};
    }
    this->mode = "pre game";
}

void ChessBoard::undo() {
    int num_moves = pastMoves.size();
    if (num_moves == 0) {
        throw Error{"Cannot undo"};
    }
    Move recent_move = pastMoves.back();
    board[recent_move.get_orig_pos().get_y_pos()][recent_move.get_orig_pos().get_x_pos()] = recent_move.get_piece();
    board[recent_move.get_final_pos().get_y_pos()][recent_move.get_final_pos().get_x_pos()] = recent_move.get_removed_piece();
    board[recent_move.get_orig_pos().get_y_pos()][recent_move.get_orig_pos().get_x_pos()]->sub_move_count();
    if (recent_move.get_enpassant()) {
        int move_unit = (recent_move.get_piece()->get_color() == 'w') ? -1 : 1;
        if (recent_move.get_piece()->get_color() == 'w') {
            board[recent_move.get_final_pos().get_y_pos() - move_unit][recent_move.get_final_pos().get_x_pos()] = make_shared<Pawn>('p');
        } else {
            board[recent_move.get_final_pos().get_y_pos() - move_unit][recent_move.get_final_pos().get_x_pos()] = make_shared<Pawn>('P');
        }
        board[recent_move.get_final_pos().get_y_pos() - move_unit][recent_move.get_final_pos().get_x_pos()]->add_move_count();
    }
    if (recent_move.get_castling()) {
        if (recent_move.get_final_pos().get_x_pos() == 6 && recent_move.get_final_pos().get_y_pos() == 0) {
            board[0][7] = board[0][5];
            board[0][7]->sub_move_count();
            board[0][5] = nullptr;
        }
        if (recent_move.get_final_pos().get_x_pos() == 2 && recent_move.get_final_pos().get_y_pos() == 0) {
            board[0][0] = board[0][3];
            board[0][0]->sub_move_count();
            board[0][3] = nullptr;
        }
        if (recent_move.get_final_pos().get_x_pos() == 6 && recent_move.get_final_pos().get_y_pos() == 7) {
            board[7][7] = board[7][5];
            board[7][7]->sub_move_count();
            board[7][5] = nullptr;
        } else {
            board[7][0] = board[7][3];
            board[7][0]->sub_move_count();
            board[7][3] = nullptr;
        }
    }
    pastMoves.pop_back();
}

void ChessBoard::undo_all() {
    this->undo();
    check_turn_switch("u");
}

void ChessBoard::move(Position pos1, Position pos2, bool is_temp_move) {
    if (computer[turn] != nullptr) {
        throw Error{"Computer's turn"};
    }
    if (board[pos1.get_y_pos()][pos1.get_x_pos()] == nullptr) {
        throw Error{"No piece detected at current position."};
    }
    if (board[pos1.get_y_pos()][pos1.get_x_pos()]->get_color() != turn) {
        throw Error{"Invalid colour."};
    }
    if (pos1.get_y_pos() == pos2.get_y_pos() && pos1.get_x_pos() == pos2.get_x_pos()) {
        throw Error{"No movement of pieces detected."};
    }
    if (board[pos1.get_y_pos()][pos1.get_x_pos()]->get_type() == 'k') {
        this->move_king(pos1, pos2);
    }
    else if (board[pos1.get_y_pos()][pos1.get_x_pos()]->get_type() == 'p') {
        this->move_pawn(pos1, pos2);
    } else {
        if (board[pos1.get_y_pos()][pos1.get_x_pos()]->valid_move(this, pos1, pos2)) {
            pastMoves.emplace_back(board[pos1.get_y_pos()][pos1.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()], pos1, pos2, false, false, false);
            board[pos2.get_y_pos()][pos2.get_x_pos()] = board[pos1.get_y_pos()][pos1.get_x_pos()];
            board[pos1.get_y_pos()][pos1.get_x_pos()]->add_move_count();
            board[pos1.get_y_pos()][pos1.get_x_pos()] = nullptr;
        }
        else {
            throw Error{"Invalid move"};
        }
    }
    if (!is_temp_move) {check_turn_switch();}
}

void ChessBoard::computer_move() {
    if (computer[turn] == nullptr) {
        throw Error{"Not computer's turn"};
    }
    vector<Position> positions = (computer[turn])->play(this);
    this->move(positions[0], positions[1], false);
}

int ChessBoard::count_pieces() {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr) {count += 1;}
        }
    }
    return count;
}

void ChessBoard::resign() {
    string result;
    if (this->turn == 'w') {
        result = "wr";
        score["Black"] += 1;
    } else {
        result = "br";
        score["White"] += 1;
    }
    char opposite_turn = (turn == 'w' ? 'b' : 'w');
    score[player[opposite_turn]] += 1;
    notifyObservers(result);
    clear_board();
}
