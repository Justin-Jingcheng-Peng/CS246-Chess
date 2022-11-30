#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "chessBoard.h"

using namespace string;

class TextObserver : public Observer {
  ChessBoard *chessBoard;

  public:
    TextObserver(ChessBoard *chessBoard);
    ~TextObserver();
    void notify(string gameResult);
};

#endif
