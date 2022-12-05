#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "chessBoard.h"
#include "position.h"
#include "computerPlayer.h"

using namespace std;

class LevelThree : public ComputerPlayer {
  vector<Position> play(ChessBoard *chessBoard) overide;
};

#endif
