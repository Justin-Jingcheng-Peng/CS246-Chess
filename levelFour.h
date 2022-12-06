#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "chessBoard.h"
#include "position.h"
#include "computerPlayer.h"

using namespace std;

class LevelFour : public ComputerPlayer {
  vector<Position> play(ChessBoard *chessBoard) override;
};

#endif
