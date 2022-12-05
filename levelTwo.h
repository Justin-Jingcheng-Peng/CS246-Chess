#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "chessBoard.h"
#include "position.h"
#include "computerPlayer.h"

using namespace std;

class LevelTwo : public ComputerPlayer {
  vector<Position> play(ChessBoard *chessBoard) overide;
};

#endif
