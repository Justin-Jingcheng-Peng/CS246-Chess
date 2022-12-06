#include "chessController.h"
#include "chessBoard.h"
#include "position.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include <iostream>
#include <sstream>

using namespace std;

ChessController::ChessController(ChessBoard *chessBoard) : chessBoard{chessBoard} {};

void ChessController::start_game(string player1, string player2) {
  if (chessBoard->get_mode() != "pre_game") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  chessBoard->add_player(player1, 'w');
  chessBoard->add_player(player2, 'b');
  chessBoard->start_game();
}

void ChessController::resign() {
  if (chessBoard->get_mode() != "game") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  chessBoard->resign();
}

void ChessController::move(string move_commands) {
  if (chessBoard->get_mode() != "game") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  else if (move_commands == "") chessBoard->computer_move();

  else {
    string mc;
    istringstream iss{move_commands};
    int size = 0;
    
    while (iss >> mc[size]) size++;

    Position from = create_position(mc[0]);
    Position to = create_position(mc[1]);

    if (size == 3) {
      char promotedPawn = mc[2][0];
      chessBoard->move_promotion(from, to, promotedPawn);
    }

    else chessBoard->move_promotion(from, to, promotedPawn);
  }
}

void ChessController::undo() {
  if (chessBoard->get_mode() != "game") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  chessBoard->undo();
}

void ChessController::setup() {
  if (chessBoard->get_mode() != "pre_game") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  chessBoard->setup();
}

void ChessController::setup_add_piece(char piece, string position) {
  if (chessBoard->get_mode() != "setup") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  if (piece == 'K' || piece == 'k') {
    chessBoard->setup_add_piece(make_shared<King>(piece), create_position(position));
  }
  else if (piece == 'Q' || piece == 'q') {
    chessBoard->setup_add_piece(make_shared<Queen>(piece), create_position(position));
  }
  else if (piece == 'R' || piece == 'r') {
    chessBoard->setup_add_piece(make_shared<Rook>(piece), create_position(position));
  }
  else if (piece == 'B' || piece == 'b') {
    chessBoard->setup_add_piece(make_shared<Bishop>(piece), create_position(position));
  }
  else if (piece == 'N' || piece == 'n') {
    chessBoard->setup_add_piece(make_shared<Knight>(piece), create_position(position));
  }
  else if (piece == 'P' || piece == 'p') {
    chessBoard->setup_add_piece(make_shared<Pawn>(piece), create_position(position));
  }
}

void ChessController::setup_remove_piece(string position) {
  if (chessBoard->get_mode() != "setup") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  chessBoard->setup_remove_piece(create_position(position));
}

void ChessController::setup_set_turn(char color) {
  if (chessBoard->get_mode() != "setup") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  chessBoard->setup_set_turn();
}

void ChessController::setup_done() {
  if (chessBoard->get_mode() != "setup") {
    throw GameError{"The current game mode is " + board->get_mode()};
  }

  chessBoard->setup_done();
}

Position ChessController::create_position(string coordinate) {
  Position coord = Position(coordinate[0] - 'a', 7 - coordinate[1] + '1');
  
  if (coord.get_x_pos() < 0 || coord.get_y_pos() < 0 || coord.get_x_pos() > 7 || coord.get_y_pos() > 7) {
		throw GameError{"not a valid position"};
	}
  
  return coord;
}