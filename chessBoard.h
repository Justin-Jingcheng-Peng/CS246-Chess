#ifndef _CHESSBOARD_H
#define _CHESSBOARD_H
#include "subject.h"
#include "bishop.h"
#include "king.h"
#include "move.h"
#include "pawn.h"
#include "piece.h"
#include "position.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "computerPlayer.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

class Error {
  private:
    std::string msg;
  public:
    Error(std::string msg): msg{msg} {}
    std::string get_msg() {return this->msg;}
};

class ChessBoard: public Subject {
    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> board;
        std::vector<Move> pastMoves;
        std::map<char, std::shared_ptr<Computer>> computer;
        std::map<std::string, int> score;
        std::map<char, std::string> player;
        std::string mode;
        char turn; // keeps track of whose turn this is by using characters 'b' and 'w' to indicate black or white.
        void set_std_board();
        bool is_empty_board(); // checks if board is empty
        void make_empty_board(); // creates an empty board
        void move_king(Position pos1, Position pos2); // handles movement of king.
        bool can_white_king_move(Position white_king_pos);
        bool can_black_king_move(Position black_king_pos);
        void castling_move(Position king_pos_1, Position king_pos_2, Position rook_pos_1, Position rook_pos_2); // handles castling
        void move_pawn(Position pos1, Position pos2); // handles movement of pawn
        void promote_pawn(Position pos1, Position pos2, char promoted_to); // handles promotion of pawns
        bool can_piece_block(Position pos);
        void check_turn_switch(std::string msg = ""); // checks current board state and checks if anyone won or if there is a stalemate
        bool is_stalemate(char colour); // checks if the current board condition shows a stalemate.
        void turn_switch(); // alternates turns between black and white
        void clear_board(); // clears the board.
    public:
        ChessBoard(); // basic constructor for board.
        ~ChessBoard(); // destructor for board.
        std::vector<std::vector<std::shared_ptr<Piece>>> get_board(); // get board.
        void set_mode(std::string mode); // Setter for the mode field.
        std::string get_mode(); // get game mode.
        Position get_piece_pos(char piece); // get position of a specific piece.
        Move get_last_move(); // get most recent move
        int get_num_moves(); // get the total number of moves made.
        char get_turn(); // get which piece's turn to move
        std::map<std::string, int> get_score(); // get score
        std::string check_board(); // checks board state.
        void start_game(); // start game.
        void add_player(std::string name, char colour); // adds new player
        void setup_add_piece(std::shared_ptr<Piece> piece, Position pos); // manually adds piece to board during setup phase.
        void setup_remove_piece(Position pos); // remove pieces at a specific position during setup phase.
        void setup_set_turn(char colour); // manually sets turn
        void setup(); // starts setup phase
        void setup_done(); // finishes setup phase
        void undo(); // undo once
        void undo_all(); // Undo all moves.
        bool is_white_checked(); // Check if white is being checked.
        bool is_black_checked(); // Check if black is being checked.
        bool is_pos_in_check(Position pos, char colour); // checks if moving a piece to that position would lead to a check
        void move(Position pos1, Position pos2, bool is_temp_move); // moves pieces from pos1 to pos2
        void move_promote(Position pos1, Position pos2, char promote);
        void computer_move(); // controls computers moves. 
        int count_pieces(); // counts the number of pieces in the board.
        void resign(); // declares one of the player resigns.
};

#endif
