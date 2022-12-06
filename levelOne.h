#ifndef LEVEL_ONE_H
#define LEVEL_ONE_H

#include "computerPlayer.h"
#include "chessBoard.h"
#include "position.h"

using namespace std;

class LevelOne : public ComputerPlayer {
  vector<Position> play(ChessBoard *chessBoard) override;
};

#endif
