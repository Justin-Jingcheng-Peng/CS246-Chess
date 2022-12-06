#include "chessController.h"
#include "chessView.h"
#include "chessBoard.h"
#include "observer.h"
#include "textObserver.h"
#include "graphicsObserver.h"
#include <iostream>

using namespace std;

void ChessView::run() {
  string command;
  auto board = make_shared<ChessBoard>();
  vector<shared_ptr<Observer>> observer;

  auto textObserver = make_shared<TextObserver>(board.get());
  auto graphicsObserver = make_shared<GraphicsObserver>(board.get());
  observer.push_back(textObserver);
  observer.push_back(graphicsObserver);
  
  ChessController chessController = ChessController(board.get());
  
  while (cin >> command) {
    // Starts a new game
    if (command == "game") {
      try {
        string player1;
        string player2;

        cin >> player1 >> player2;
        chessController.start_game(player1, player2);
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }
    }

    // Concedes game to the opponent
    else if (command == "resign") {
      try {
        chessController.resign();
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }
    }

    // Moves a piece
    else if (command == "move") {
      try {
        string commands;
        getline(cin, commands);
        chessController.move(commands);
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }
    }

    // Undo previous move
    else if (command == "undo") {
      try {
        chessController.undo();
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }
    }

    // Enter setup mode, allowing the user to set up their own initial board configurations
    else if (command == "setup") {
      try {
       chessController.setup(); 
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }
    }

    /* The following commands are used during setup mode */

    // Adds a piece on a square
    else if (command == "+") {
      try {
        char piece;
        string square;
        cin >> piece >> square;

        chessController.setup_add_piece(piece, square);
        board->notifyObservers("n");
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }
    }

    // Removes a piece from a square
    else if (command == "-") {
      try {
        string square;
        cin >> square;

        chessController.setup_remove_piece(square);
        board->notifyObservers("n");
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }      
    }

    // Makes it color's turn to go next
    else if (command == "=") {
      try {
        char color;
        cin >> color;

        chessController.setup_set_turn(color);
        board->notifyObservers("n");
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }     
    }

    // Leaves setup mode
    else if (command == "done") {
      try {
        chessController.setup_done();
      }

      catch (Error err) {
        cout << "Game error: " << err.get_msg() << endl;
      }     
    }
  }
}
