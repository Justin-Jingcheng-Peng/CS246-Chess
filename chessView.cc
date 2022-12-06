#include "chessController.h"
#include "chessView.h"
#include "observer.h"
#include "textObserver.h"
#include "graphicsObserver.h"
#include <iostream>

using namespace std;

void ChessView::run() {
  string command;
  auto chessBoard = make_shared<Board>();
  vector<shared_ptr<Observer>> observer;

  auto textObserver = make_shared<TextObserver>(chessBoard.get());
  auto graphicsObserver = make_shared<GraphicsObserver>(chessBoard.get());
  observer.push_back(textObserver);
  observer.push_back(graphicsObserver);
  
  ChessController chessController = ChessController(chessBoard.get());
  
  while (cin >> command) {
    // Starts a new game
    if (command == "game") {
      try {
        string player1;
        string player2;

        cin >> player1 >> player2;
        chessController.start();
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
      }
    }

    // Concedes game to the opponent
    else if (command == "resign") {
      try {
        chessController.resign();
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
      }
    }

    // Moves a piece
    else if (command == "move") {
      try {
        string commands;
        getline(cin, commands);
        chessControllermove(commands);
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
      }
    }

    // Undo previous move
    else if (command == "undo") {
      try {
        chessController.undo();
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
      }
    }

    // Enter setup mode, allowing the user to set up their own initial board configurations
    else if (command == "setup") {
      try {
       chessController.setup(); 
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
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
        chessBoard->notifyObservers("n");
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
      }
    }

    // Removes a piece from a square
    else if (command == "-") {
      try {
        string square;
        cin >> square;

        chessController.setup_remove_piece(square);
        chessBoard->notifyObservers("n");
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
      }      
    }

    // Makes it color's turn to go next
    else if (command == "=") {
      try {
        char color;
        cin >> color;

        chessController.setup_set_turn(color);
        chessBoard->notifyObservers("n");
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
      }     
    }

    // Leaves setup mode
    else if (command == "done") {
      try {
        chessController.setup_done();
      }

      catch (GameError err) {
        cout << "Game error: " << err.get_message() << endl;
      }     
    }
  }
}
