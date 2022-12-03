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
  
}
