#include "graphicsObserver.h"
#include "observer.h"
#include "chessBoard.h"
#include "window.h"
#include <memory>

using namespace std;

GraphicsObserver::GraphicsObserver(ChessBoard *chessBoard) : 
chessBoard{chessBoard}, 
window{make_shared<Xwindow>(480, 480) {
  chessBoard->attach(this);
}

GraphicsObserver::~GraphicsObserver() {
  chessBoard->detach(this);
}

void GraphicsObserver::notify(string gameResult) {
  
}
