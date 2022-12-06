#ifndef CHESS_CONTROLLER_H
#define CHESS_CONTROLLER_H
#include "chessBoard.h"
#include <memory>
#include "position.h"

using namespace std;

class ChessController {
  ChessBoard *chessBoard;
  Position create_position(string coordinate);

public:
  ChessController(ChessBoard *chessBoard);
  void start_game(string player1, string player2);
  void resign();
  void move(string move_commands);
  void undo();
  void setup();
  void setup_add_piece(char piece, string position);
  void setup_remove_piece(string position);
  void setup_set_turn(char color);
  void setup_done();
};

#endif
