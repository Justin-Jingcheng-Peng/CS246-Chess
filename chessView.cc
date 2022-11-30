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

      catch () {
        
      }
    }

    // Concedes game to the opponent
    else if (command == "resign") {
      try {
        chessController.resign();
      }

      catch () {
        
      }
    }

    // Moves a piece
    else if (command == "move") {
      try {
        string move_commands;
      }

      catch () {
        
      }
    }

    // Undo previous move
    else if (command == "undo") {
      try {
        chessController.undo();
      }

      catch () {
        
      }
    }

    // Enter setup mode, allowing the user to set up their own initial board configurations
    else if (command == "setup") {
      try {
        
      }

      catch () {
        
      }
    }

    /* The following commands are used during setup mode */

    // Adds a piece on a square
    else if (command == "+") {
     try {
        
      }

      catch () {
        
      }  
    }

    // Removes a piece from a square
    else if (command == "-") {
     try {
        
      }

      catch () {
        
      }      
    }

    // Makes it color's turn to go next
    else if (command == "=") {
      try {
        
      }

      catch () {
        
      }      
    }

    // Leaves setup mode
    else if (command == "done") {
      try {
        
      }

      catch () {
        
      }      
    }
  }
}
