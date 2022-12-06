#include "levelThree.h"
#include "computerPlayer.h"
#include "chessBoard.h"
#include "position.h"

vector<Position> LevelThree::play(ChessBoard *chessBoard) {
  vector<vector<Position>> moves = get_moves(chessBoard, chessBoard->get_turn());
  vector<vector<Position>> attackingMoves = get_attacking_moves(chessBoard, moves);
  vector<vector<Position>> escapingMoves = get_escaping_moves(chessBoard, moves);
  vector<vector<Position>> checkMoves = get_check_moves(chessBoard, moves);

  int numOfMoves = moves.size();
  int numOfAttackingMoves = attackingMoves.size();
  int numOfEscapingMoves = escapingMoves.size();
  int numOfCheckMoves = checkMoves.size();

  if (numOfAttackingMoves != 0) return attackingMoves[randomizer(0, numOfAttackingMoves)];
  if (numOfCheckMoves != 0) return checkMoves[randomizer(0, numOfCheckMoves)];
  if (numOfEscapingMoves != 0) return escapingMoves[randomizer(0, numOfEscapingMoves)];
  else return moves[randomizer(0, numOfMoves)];
}
