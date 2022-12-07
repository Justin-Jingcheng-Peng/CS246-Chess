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
	    void set_standard_board(); // creates a standard chess board
	    bool is_empty_board(); // checks if the board is empty
	    void make_empty_board(); // creates an empty board
	    void move_king(Position pos1, Position pos2); // handles all the movements of the King piece
	    void move_pawn(Position pos1, Position pos2); // handles all the movements of the Pawn piece
	    void castling_move(Position king_from, Position king_to, Position rook_from, Position rook_to); // handles castling
	    void promote_pawn(Position from, Position to, char promoted); // handles promotion of pawns
	    void handle_next_turn(std::string message = ""); // handles whether a change of turn is valid
	    bool is_piece_blockable(Position pos); // Checks if any of the pieces can be blocked.
	    bool is_stalemate(char color); // Checks for stalemate
	    bool can_piece_move(Position pos); // Checks if a piece at a specific position can move
	    void change_turn(); // Changes the turn from white to black and vice versa.
	    void clear_board(); // Clears the board.
    public:
	    ~ChessBoard(); // dtor for ChessBoard class
	    ChessBoard(); // ctor for ChessBoard class
	    std::vector<std::vector<std::shared_ptr<Piece>>> get_board(); // getter for board field
	    void add_player(std::string name, char color); // Adds players by inserting it into the player map
	    void start_game(); // starts the game
	    void setup_add_piece(std::shared_ptr<Piece> piece, Position pos); // adds pieces during setup phase.
	    void setup_remove_piece(Position pos); // removes pieces during setup phase.
	    void setup_set_turn(char color); // Manually sets turn during setup phase.
	    void setup_done(); // Finishes setup.
	    void move(Position from, Position to, bool is_temp_move); // moves pieces from one position to another
	    void computer_move(); // handles computer movements
	    bool is_position_check(Position pos, char color); // Checks if a position is in check.
	    void move_promote(Position from, Position to, char promoted); // Handles promotion when moving
	    std::string check_board(); // Checks the board state.
	    void undo(); // undo a move
	    void undo_all(); // undo all moves
	    std::map<std::string, int> get_scores(); // get the scores of each player
	    void set_mode(std::string mode); // Sets the game mode
	    std::string get_mode(); // getter for game_mode field
	    Move get_last_move(); // gets the most recent move
	    int get_num_moves(); // gets the total number of moves
	    void setup(); // enters setup phase
	    int count_pieces(); // Counts the total number of pieces on the board.
	    void resign(); // When one of the players surrender
	    char get_turn(); // Get the current turn.
	    Position get_piece_pos(char piece); // Get position of a specific piece.
};

#endif
