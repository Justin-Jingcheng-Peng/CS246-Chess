#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "subject.h"
#include <memory>
#include <map>
#include <vector>
#include "move.h"
#include "position.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "computerPlayer.h"
#include <string>

class Error {
  private:
    string msg;
  public:
    Error(string msg): msg{msg} {}
    string get_msg() {return this->msg;}
};

class ChessBoard : public Subject {
    private:
	    std::map<char, std::shared_ptr<ComputerPlayer>> computer;
	    std::vector<Move> pastMoves;
	    std::map<char, std::string> player;
	    std::map<std::string, int> score;
	    std::vector<std::vector<std::shared_ptr<Piece>>> board;
        std::string game_mode;
	    char turn;
	    void set_standard_board();
	    bool is_empty_board();
	    void make_empty_board();
	    void move_king(Position pos1, Position pos2);
	    void move_pawn(Position pos1, Position pos2);
	    void castling_move(Position king_from, Position king_to, Position rook_from, Position rook_to);
	    void promote_pawn(Position from, Position to, char promoted);
	    void handle_next_turn(std::string message = "");
	    bool is_piece_blockable(Position pos);
	    bool is_stalemate(char color);
	    bool can_piece_move(Position pos);
	    void change_turn();
	    void clear_board();
    public:
	    ~ChessBoard();
	    ChessBoard();
	    std::vector<std::vector<std::shared_ptr<Piece>>> get_board();
	    void add_player(std::string name, char color);
	    void start_game();
	    void setup_add_piece(std::shared_ptr<Piece> piece, Position pos);
	    void setup_remove_piece(Position pos);
	    void setup_set_turn(char color);
	    void setup_done();
	    void move(Position from, Position to, bool is_temp_move);
	    void computer_move();
	    bool is_position_check(Position pos, char color);
	    void move_promote(Position from, Position to, char promoted);
	    std::string check_board();
	    void undo();
	    void undo_all();
	    std::map<std::string, int> get_scores();
	    void set_mode(std::string mode);
	    std::string get_mode();
	    Move get_last_move();
	    int get_num_moves();
	    void setup();
	    int count_pieces();
	    void resign();
	    char get_turn();
	    Position get_piece_pos(char piece);
};

#endif
