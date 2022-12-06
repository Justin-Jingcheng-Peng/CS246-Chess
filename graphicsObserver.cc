#include "graphicsObserver.h"
#include "observer.h"
#include "chessBoard.h"
#include "piece.h"
#include "window.h"
#include <memory>
#include <string>

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
  if (gameResult == "sr") return;

  vector<vector<shared_ptr<Piece>>> chessBoardVector = chessBoard->get_board();
  if ()
  for (int i = 8; i > 0; i--) {
    xw->drawString(25, 25 + 50 * abs(i - 8), to_string(i));
  }

  char c = 'a';
  for (int i - 75; i <=425; i+= 50) {
    string s;
    s += c;
    window->drawString(i, 420, s);
    c++;
  }
}
