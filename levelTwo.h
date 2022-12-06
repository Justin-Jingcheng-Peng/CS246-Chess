#ifndef LEVEL_TWO_H
#define LEVEL_TWO_H

#include "chessBoard.h"
#include "position.h"
#include "computerPlayer.h"

using namespace std;

class LevelTwo : public ComputerPlayer {
  vector<Position> play(ChessBoard *chessBoard) override;
};

#endif
