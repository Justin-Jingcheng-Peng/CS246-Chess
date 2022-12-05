#ifndef LEVELONE_H
#define LEVELONE_H

#include "computerPlayer.h"
#include "chessBoard.h"
#include "position.h"

using namespace std;

class LevelOne : public ComputerPlayer {
  vector<Position> play(ChessBoard *chessBoard) overide;
};

#endif
