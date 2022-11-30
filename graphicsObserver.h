#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "chessBoard.h"
#include "observer.h"
#include "window.h"
#include <memory>

using namespace std;

class GraphicsObserver : public Observer {
  ChessBoard *chessBoard;
  shared_ptr<Xwindow> window = nullptr;

public:
  GraphicsObserver(ChessBoard *chessBoard);
  ~GraphicsObserver();
  void notify(string gameResult) override;
};

#endif
