#include "levelOne.h"
#include "computerPlayer.h"
#include "chessBoard.h"
#include "position.h"

vector<Position> LevelOne::play(ChessBoard *chessBoard) {
  vector<vector<Position>> moves = get_moves(chessBoard, chessBoard->get_turn());
  int numOfMoves = moves.size();
  return moves[randomizer(0, numOfMoves)];
}
