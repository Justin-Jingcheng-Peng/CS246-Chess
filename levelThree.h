#ifndef LEVEL_THREE_H
#define LEVEL_THREE_H

#include "chessBoard.h"
#include "position.h"
#include "computerPlayer.h"

using namespace std;

class LevelThree : public ComputerPlayer {
  vector<Position> play(ChessBoard *chessBoard) override;
};

#endif
