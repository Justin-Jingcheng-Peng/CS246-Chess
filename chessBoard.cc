#include "chessBoard.h"
#include <cmath>
#include <string>
#include "computerPlayer.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"

using namespace std;

ChessBoard::ChessBoard()
{
	score["White"] = 0;
	score["Black"] = 0;
    this->turn = ' ';
	this->game_mode = "pre_game";
	make_empty_board();
}

ChessBoard::~ChessBoard() {
	board.clear();		
}

void ChessBoard::set_mode(std::string mode) {
    this->game_mode = mode;
}

string ChessBoard::get_mode() {return this->game_mode;}

void ChessBoard::handle_next_turn(string message) {
    string result = this->check_board();
    bool has_game_ended = false;
    if (result == "be") {
        score["Black"] += 1;
        score[player[result[0]]] += 1;
        has_game_ended = true;
    }
    else if (result == "we") {
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
    else {this->change_turn();}
    if (message == "") {
        this->notifyObservers(result);
    }
    else {
        this->notifyObservers(message + result);
    }
    if (has_game_ended) {clear_board();}
}

void ChessBoard::clear_board() {
    this->make_empty_board();
    pastMoves.clear();
    player.clear();
    this->turn = 'w';
    this->game_mode = "pre_game";
}

map<std::string, int> ChessBoard::get_scores() {return this->score;}

string ChessBoard::check_board() {
    if (this->count_pieces() == 2) { // Checks basic stalemate
        return "s";
    }
    bool white_checked = this->is_position_check(get_piece_pos('K'), 'w');
    bool black_checked = this->is_position_check(get_piece_pos('k'), 'b');
    bool white_in_stalemate = this->is_stalemate('w');
    bool black_in_stalemate = this->is_stalemate('b');
    // game can still be played "normal" state.
    if (!white_in_stalemate && !black_in_stalemate && !white_checked && !black_checked) {return "n";}
    // stalemate condition
    if ((white_in_stalemate || black_in_stalemate) && !white_checked && !black_checked) {return "s";}
    if ((this->turn == 'w' && white_checked) || (this->turn == 'b' && black_checked)) {
        this->undo();
        throw Error{"Invalid. You are/will be in check!"};
    }
    Move recent_move = this->get_last_move();
    bool can_defend = this->is_piece_blockable(recent_move.get_final_pos());
    bool white_king_can_move = this->can_piece_move(this->get_piece_pos('K'));
    bool black_king_can_move = this->can_piece_move(this->get_piece_pos('k'));
    // White checkmates black
    if (black_checked && !black_king_can_move && !can_defend) {
        return "we";
    }
    // Black checkmates white
    if (white_checked && !white_king_can_move && !can_defend) {
        return "be";
    }
    // White checks black
    if (black_checked && (black_king_can_move || can_defend)) {
        return "wc";
    }
    // Black checks White
    if (white_checked && (white_king_can_move || can_defend)) {
        return "bc";
    }
    // Return "normal state" otherwise
    return "n";
}

bool ChessBoard::can_piece_move(Position pos) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i != pos.get_y_pos() || j != pos.get_x_pos()) && board[pos.get_y_pos()][pos.get_x_pos()]->valid_move(this, pos, Position(j,i))) {
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::is_stalemate(char color) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((board[i][j] != nullptr) && (board[i][j]->get_color() == color)) {
                for (int m = 0; m < 8; ++m) {
                    for (int n = 0; n < 8; ++n) {
                        if ((n != i || m != j) && board[i][j]->valid_move(this, Position(j,i), Position(n,m))) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool ChessBoard::is_piece_blockable(Position pos) {
    if (board[pos.get_y_pos()][pos.get_x_pos()]->get_type() == 'n') {
        if (this->is_position_check(pos, board[pos.get_y_pos()][pos.get_x_pos()]->get_color())) {
            return true;
        } else {
            return false;
        }
    }
    char king = 'K';
    if (board[pos.get_y_pos()][pos.get_x_pos()]->get_color() == 'w') {
        king = 'k';
    }
    Position op_king_pos = this->get_piece_pos(king);
    int move_x = 0;
    if (op_king_pos.get_x_pos() - pos.get_x_pos() != 0) {
        move_x = (op_king_pos.get_x_pos() - pos.get_x_pos() > 0 ? 1 : -1);
    }
    int move_y = 0;
    if (op_king_pos.get_y_pos() - pos.get_y_pos() != 0) {
        move_y = (op_king_pos.get_y_pos() - pos.get_y_pos() > 0 ? 1 : -1);
    }
    int cur_x = pos.get_x_pos();
    int cur_y = pos.get_y_pos();
    while (cur_x != op_king_pos.get_x_pos() || cur_y != op_king_pos.get_y_pos()) {
        if (this->is_position_check(Position(cur_x, cur_y), board[pos.get_y_pos()][pos.get_x_pos()]->get_color())) {
            return true;
        }
        cur_x += move_x;
        cur_y += move_y;
    }
    return false;
}

Position ChessBoard::get_piece_pos(char piece) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->get_symbol() == piece) {
                return Position(j,i);
            }
        }
    }
    return Position(-1,-1);
}

void ChessBoard::undo_all() {
    this->undo();
    this->handle_next_turn("u");
}

void ChessBoard::undo() {
    int move_count = pastMoves.size();
    if (move_count == 0) {
        throw Error{"Cannot undo any further."};
    }
    Move recent_move = this->get_last_move();
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

void ChessBoard::computer_move() {
    if (computer[turn] == nullptr) {
        throw Error{"Not computer's turn"};
    }
    vector<Position> positions = (computer[turn])->play(this);
    this->move(positions[0], positions[1], false);
}

void ChessBoard::move(Position from, Position to, bool is_temp_move) {
    if (computer[turn] != nullptr) {
        throw Error{"It's the computer's turn"};
    }
    if (board[from.get_y_pos()][from.get_x_pos()] == nullptr) {
        throw Error{"No piece detected in the current position"};
    }
    if (board[from.get_y_pos()][from.get_x_pos()]->get_color() != turn) {
        throw Error{"Invalid piece color."};
    }
    if (from.get_x_pos() == to.get_x_pos() && from.get_y_pos() == to.get_y_pos()) {
        throw Error{"No movement detected."};
    }
    if (board[from.get_y_pos()][from.get_x_pos()]->get_type() == 'k') {
        this->move_king(from, to);
    }
    else if (board[from.get_y_pos()][from.get_x_pos()]->get_type() == 'p') {
        this->move_pawn(from, to);
    }
    else {
        if (board[from.get_y_pos()][from.get_x_pos()]->valid_move(this, from, to)) {
            pastMoves.emplace_back(board[from.get_y_pos()][from.get_x_pos()], board[to.get_y_pos()][to.get_x_pos()], from, to, false, false, false);
            board[to.get_y_pos()][to.get_x_pos()] = board[from.get_y_pos()][from.get_x_pos()];
            board[from.get_y_pos()][from.get_x_pos()]->add_move_count();
            board[from.get_y_pos()][from.get_x_pos()] = nullptr;
        }
        else {
            throw Error{"Invalid move."};
        }
    }
    if (!is_temp_move) {
        handle_next_turn();
    }
}

void ChessBoard::move_promote(Position from, Position to, char promoted) {
    if (board[from.get_y_pos()][from.get_x_pos()]->get_type() != 'p') {
        throw Error{"No pawn detected in the current position."};
    }
    if (promoted != 'r' && promoted != 'R' && promoted != 'n' && promoted != 'N' && promoted != 'b' && promoted != 'B' && promoted != 'q' && promoted != 'Q') {
        throw Error{"You can only promote the pawn to either a bishop, rook, knight or queen."};
    }
    if (board[from.get_y_pos()][from.get_x_pos()]->valid_move(this, from, to) && ((board[from.get_y_pos()][from.get_x_pos()]->get_color() == 'w' && to.get_y_pos() == 0) || (board[from.get_y_pos()][from.get_x_pos()]->get_color() == 'b' && to.get_y_pos() == 7))) {
        this->promote_pawn(from, to, promoted);
    }
    else {
        throw Error{"Invalid promotion."};
    }
    handle_next_turn();
}

void ChessBoard::promote_pawn(Position from, Position to, char promoted) {
    char color = (promoted < 'a') ? 'w' : 'b';
    if (color != board[from.get_y_pos()][from.get_x_pos()]->get_color()) {
        throw Error{"Promoted and piece color don't match"};
    }
    pastMoves.emplace_back(board[from.get_y_pos()][from.get_x_pos()], board[to.get_y_pos()][to.get_x_pos()], from, to, false, false, true);
    board[from.get_y_pos()][from.get_x_pos()] = nullptr;
    if (promoted == 'r' || promoted == 'R') {
        board[to.get_y_pos()][to.get_x_pos()] = make_shared<Rook>(promoted);
    }
    if (promoted == 'b' || promoted == 'B') {
        board[to.get_y_pos()][to.get_x_pos()] = make_shared<Bishop>(promoted);
    }
    if (promoted == 'n' || promoted == 'N') {
        board[to.get_y_pos()][to.get_x_pos()] = make_shared<Knight>(promoted);
    }
    else {
        board[to.get_y_pos()][to.get_x_pos()] = make_shared<Queen>(promoted);
    }
    board[to.get_y_pos()][to.get_x_pos()]->add_move_count();
}

void ChessBoard::move_king(Position pos1, Position pos2) {
    if (!board[pos1.get_y_pos()][pos1.get_x_pos()]->valid_move(this, pos1, pos2)) {
        throw Error{"Invalid King/Castling move"};
    }
    if (pos1.dist_squared(pos2) <= 2) {
        pastMoves.emplace_back(board[pos1.get_y_pos()][pos2.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()], pos1, pos2, false, false, false);
        board[pos2.get_y_pos()][pos2.get_x_pos()] = board[pos1.get_y_pos()][pos1.get_x_pos()];
        board[pos1.get_y_pos()][pos1.get_x_pos()]->add_move_count();
        board[pos1.get_y_pos()][pos1.get_x_pos()] = nullptr;
    }
    //check castling
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

void ChessBoard::castling_move(Position king_from, Position king_to, Position rook_from, Position rook_to) {
    pastMoves.emplace_back(board[king_from.get_y_pos()][king_from.get_x_pos()], nullptr, king_from, king_to, true, false, false);
    board[king_to.get_y_pos()][king_to.get_x_pos()] = board[king_from.get_y_pos()][king_from.get_x_pos()];
    board[king_to.get_y_pos()][king_to.get_x_pos()]->add_move_count();
    board[rook_to.get_y_pos()][rook_to.get_x_pos()] = board[rook_from.get_y_pos()][rook_from.get_x_pos()];
    board[rook_to.get_y_pos()][rook_to.get_x_pos()]->add_move_count();
    board[king_from.get_y_pos()][king_from.get_x_pos()] = nullptr;
    board[rook_from.get_y_pos()][rook_from.get_x_pos()] = nullptr;
}

bool ChessBoard::is_position_check(Position pos, char color) {
    shared_ptr<Piece> tmp = board[pos.get_y_pos()][pos.get_x_pos()];
    char queen = (color == 'w' ? 'Q' : 'q');
    board[pos.get_y_pos()][pos.get_x_pos()] = make_shared<Queen>(queen);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((board[i][j] != nullptr) && (board[i][j]->get_color() == color)) {
                continue;
            }
            if ((board[i][j] != nullptr) && board[i][j]->valid_move(this, Position(j,i), pos)) {
                board[pos.get_y_pos()][pos.get_x_pos()] = tmp;
                return true;
            }
        }
    }
    board[pos.get_y_pos()][pos.get_x_pos()] = tmp;
    return false;
}

void ChessBoard::move_pawn(Position pos1, Position pos2) {
    if (!board[pos1.get_y_pos()][pos1.get_x_pos()]->valid_move(this, pos1, pos2)) {
        throw Error{"Invalid Pawn move"};
    }
    if (pos2.get_x_pos() != pos1.get_x_pos() && board[pos2.get_y_pos()][pos2.get_x_pos()] == nullptr) {
        Move recent_move = this->get_last_move();
        pastMoves.emplace_back(board[pos1.get_y_pos()][pos1.get_x_pos()], board[pos2.get_y_pos()][pos2.get_x_pos()],pos1, pos2, false, true, false);
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

void ChessBoard::make_empty_board() {
    // board.clear();
    for (int i = 0; i < 8; ++i) {
        vector<shared_ptr<Piece>> row;
        for (int j = 0; j < 8; ++j) {
            row.push_back(nullptr);
        }
        board.push_back(row);
    }
}

vector<vector<shared_ptr<Piece>>> ChessBoard::get_board() {return this->board;}

void ChessBoard::add_player(string name, char color) {
    player[color] = name;
    if (name == "computer1") {computer[color] = make_shared<LevelOne>();}
    else if (name == "computer2") {computer[color] = make_shared<LevelTwo>();}
    else if (name == "computer3") {computer[color] = make_shared<LevelThree>();}
    else if (name == "computer4") {computer[color] = make_shared<LevelFour>();}
}

void ChessBoard::start_game() {
    if (player.size() != 2) {
        throw Error{"Two players required to play chess"};
    }
    if (this->is_empty_board()) {
        this->set_standard_board();
        turn = 'w';
    }
    if (turn != 'w' && turn != 'b') {turn = 'w';}
    this->game_mode = "game";
    this->notifyObservers("n");
}

void ChessBoard::setup_add_piece(shared_ptr<Piece> piece, Position pos) {
    board[pos.get_y_pos()][pos.get_x_pos()] = piece;
}

void ChessBoard::setup_remove_piece(Position pos) {
    board[pos.get_y_pos()][pos.get_x_pos()] = nullptr;
}

void ChessBoard::setup_set_turn(char color) {
    this->turn = color;
}

void ChessBoard::setup_done() {
    Position white_king = this->get_piece_pos('K');
    Position black_king = this->get_piece_pos('k');
    if ((white_king.get_x_pos() == -1 || white_king.get_y_pos() == -1) || (black_king.get_x_pos() == -1 || black_king.get_y_pos() == -1)) {
        throw Error{"Both the White King and the Black King must be in the game."};
    }
    if (is_position_check(white_king, 'w') || is_position_check(black_king, 'b')) {
        throw Error{"Kings should not in check."};
    }
    for (int i = 0; i < 8; ++i) {
        if ((board[0][i] != nullptr && board[0][i]->get_type() == 'p') || (board[7][i] != nullptr && board[7][i]->get_type() == 'p')) {
            throw Error{"Pawns should not be in the first and last rows."};
        }
    }
    int white_count = 0; 
    int black_count = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->get_symbol() == 'k') {
                black_count += 1;
            }
            if (board[i][j] != nullptr && board[i][j]->get_symbol() == 'K') {
                white_count += 1;
            }
        }
    }
    if (white_count != 1 || black_count != 1) {
        throw Error{"There should only be one White King and one Black King."};
    }
    this->game_mode = "pre_game";
}

void ChessBoard::set_standard_board() {
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
            if (board[i][j] != nullptr) {return false;}
        }
    }
    return true;
}

void ChessBoard::change_turn() {
    if (turn == 'w') {
        turn = 'b';
    }
    else {
        turn = 'w';
    }
}

Move ChessBoard::get_last_move() {return pastMoves.back();}

int ChessBoard::get_num_moves() {return pastMoves.size();} 

void ChessBoard::setup() {this->game_mode = "setup";} 

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

char ChessBoard::get_turn() {return this->turn;}
