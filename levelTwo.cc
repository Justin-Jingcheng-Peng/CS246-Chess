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

  if (numOfAttackingMoves != 0) return attackingMoves[get_random(0, numOfAttackingMoves)];
  if (numOfCheckMoves != 0) return checkMoves[get_random(0, numOfCheckMoves)];
  else return moves[get_random(0, numOfMoves)];
}
