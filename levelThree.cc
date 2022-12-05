#include "levelThree.h"
#include "computerPlayer.h"
#include "chessBoard.h"
#include "position.h"

vector<Position> LevelThree::play(ChessBoard *chessBoard) {
  vector<vector<Position>> moves = get_moves(chessBoard, chessBoard->get_turn());
  vector<vector<Position>> attackingMoves = get_attacking_moves(chessBoard, chessBoard->get_turn());
  vector<vector<Position>> escapingMoves = get_attacking_moves(chessBoard, chessBoard->get_turn());
  vector<vector<Position>> checkMoves = get_check_moves(chessBoard, chessBoard->get_turn());

  int numOfMoves = moves.size();
  int numOfAttackingMoves = attackingMoves.size();
  int numOfEscapingMoves = escapingMoves.size();
  int numOfCheckMoves = checkMoves.size();

  if (numOfAttackingMoves != 0) return attackingMoves[get_random(0, numOfAttackingMoves)];
  if (numOfCheckMoves != 0) return checkMoves[get_random(0, numOfCheckMoves)];
  if (numOfEscapingMoves != 0) return escapingMoves[get_random(0, numOfEscapingMoves)];
  else return moves[get_random(0, numOfMoves)];
}
