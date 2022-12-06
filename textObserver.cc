#include "textObserver.h"
#include "observer.h"
#include "chessBoard.h"

using namespace std;

TextObserver::TextObserver(ChessBoard *chessBoard) : chessBoard{chessBoard} {
  chessBoard->attach(this);
}

TextObserver::~TextObserver() {
  // map<string, int> score = chessBoard->get_score();
  // cout << "Final Score:" << endl;
  // for (auto it = score.begin(); it != score.end(); ++it) {
  //   cout << it->first << ": " << it->second << endl;
  // }
  
  chessBoard->detach(this);
}

TextObserver::notify(string gameResult) {
  if (gameResult != "sr") {
    std::vector<std::vector<std::shared_ptr<Piece>>> board_arr = chessBoard->get_board();
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        if (board_arr[i][j] == nullptr) {
          if ((i+j) % 2 == 1) {std::cout << '_';}
          else {std::cout << ' ';}
        }
        else{
          std::cout << chessBoard[i][j]->get_symbol();
        }
      }
      std::cout << std::endl;
    }
  }
  std::cout << std::endl << "  abcdefgh" << std::endl;
  std::cout << std::endl << std::endl;
  if (gameResult == "be" || gameResult == "ube") {
    std::cout << "Checkmate! Black wins!" << std::endl;
  }
  else if (gameResult == "we" || gameResult == "uwe") {
    std::cout << "Checkmate! White wins!" << std::endl;
  }
  else if (gameResult == "wc" || gameResult == "uwc") {
    std::cout << "Black in check." << std::endl;
  }
  else if (gameResult == "bc" || gameResult == "ubc") {
    std::cout << "White in check." << std::endl;
  }
  else if (gameResult == "s" || gameResult == "us") {
    std::cout << "Stalemate!" << std::endl;
  }
  else if (gameResult == "wr" || gameResult == "uwr") {
    std::cout << "Black wins!" << std::endl;
  }
  else if (gameResult == "br" || gameResult == "ubr") {
    std::cout << "White wins!" << std::endl;
  }
  if (gameResult == "s" || )
}
