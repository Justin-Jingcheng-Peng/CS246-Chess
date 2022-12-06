#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include <vector>
#include <cstdlib>
#include <cmath>
#include "chessBoard.h"
#include "observer.h"
#include "window.h"
#include <memory>

using namespace std;

class GraphicsObserver : public Observer {
  ChessBoard *chessBoard;
  shared_ptr<Xwindow> window = nullptr;
  bool isRed = false;
public:
  GraphicsObserver(ChessBoard *chessBoard);
  ~GraphicsObserver();
  void notify(string gameResult) override;
};

#endif
