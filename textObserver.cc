#include "textObserver.h"
#include "observer.h"

using namespace std;

TextObserver::TextObserver(ChessBoard *chessBoard) : chessBoard{chessBoard} {
  chessBoard->attach(this);
}

TextObserver::~TextObserver() {
  map<string, int> score = chessBoard->get_score();
  cout << "Final Score:" << endl;
  map<string, int>::iterator it;
  for (it = score.begin(); it != score.end(); ++it) {
    cout << it->first << ": " << it->second << endl;
  }
  chessBoard->detach(this);
}

void TextObserver::notify(string gameResult) {
  if (gameResult != "sr") {
    vector<vector<shared_ptr<Piece>>> board_arr = chessBoard->get_board();
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (board_arr[i][j] == nullptr) {
          if ((i+j) % 2 == 1) {cout << '_';}
          else {cout << ' ';}
        }
        else{
          cout << board_arr[i][j]->get_symbol();
        }
      }
      cout << endl;
    }
  }
  cout << endl << "  abcdefgh" << endl;
  cout << endl << endl;
  if (gameResult == "be" || gameResult == "ube") {
    cout << "Checkmate! Black wins!" << endl;
  }
  else if (gameResult == "we" || gameResult == "uwe") {
    cout << "Checkmate! White wins!" << endl;
  }
  else if (gameResult == "wc" || gameResult == "uwc") {
    cout << "Black in check." << endl;
  }
  else if (gameResult == "bc" || gameResult == "ubc") {
    cout << "White in check." << endl;
  }
  else if (gameResult == "s" || gameResult == "us") {
    cout << "Stalemate!" << endl;
  }
  else if (gameResult == "wr" || gameResult == "uwr") {
    cout << "Black wins!" << endl;
  }
  else if (gameResult == "br" || gameResult == "ubr") {
    cout << "White wins!" << endl;
  }
  if (gameResult == "s" || gameResult == "us" || gameResult == "we" || gameResult == "uwe" || gameResult == "be" || gameResult == "ube" || gameResult == "sr" || gameResult == "wr" || gameResult == "uwr" || gameResult == "br" || gameResult == "ubr") {
    map<string, int> score = chessBoard->get_score();
    cout << endl << "Final Score:" << endl;
    map<string, int>::iterator it;
    for (it = score.begin(); it != score.end(); it++) {
      cout << it->first << ": " << it->second << endl;
    }
  }
}
