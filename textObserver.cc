#include "textObserver.h"
#include "observer.h"
#include "chessBoard.h"

using namespace std;

TextObserver::TextObserver(ChessBoard *chessBoard) : chessBoard{chessBoard} {
  chessBoard->attach(this);
}

TextObserver::~TextObserver() {
  
}

TextObserver::notify(string gameResult) {
  
}
