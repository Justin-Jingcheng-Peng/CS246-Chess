#include "levelTwo.h"
#include "computerPlayer.h"
#include "chessBoard.h"
#include "position.h"

using namespace std;

vector<Position> LevelTwo::play(ChessBoard *chessBoard) {
  vector<vector<Position>> moves = get_moves(chessBoard, chessBoard->get_turn());
  vector<vector<Position>> attackingMoves = get_attacking_moves(chessBoard, chessBoard->get_turn());
  vector<vector<Position>> checkMoves = get_check_moves(chessBoard, chessBoard->get_turn());

  int numOfMoves = moves.size();
  int numOfAttackingMoves = attackingMoves.size();
  int numOfCheckMoves = checkMoves.size();

  if (numOfAttackingMoves != 0) return attackingMoves[randomizer(0, numOfAttackingMoves)];
  if (numOfCheckMoves != 0) return checkMoves[randomizer(0, numOfCheckMoves)];
  else return moves[randomizer(0, numOfMoves)];
}
