#ifndef _GRAPHICSOBSERVER_H_
#define _GRAPHICSOBSERVER_H_
#include <vector>
#include "observer.h"
#include <memory>
#include "window.h"
#include "chessBoard.h"

class GraphicsObserver : public Observer
{
  ChessBoard * board;
  std::shared_ptr<Xwindow> xw = nullptr;
  bool is_red = false;
public:
  GraphicsObserver(ChessBoard * board);
  void notify(std::string result) override;
  ~GraphicsObserver();
};

#endif
