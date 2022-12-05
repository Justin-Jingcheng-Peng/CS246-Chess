#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>

using namespace std;

class ChessBoard;
class Position;
class Piece;

class ComputerPlayer {
protected:
  vector<vector<Position>> get_moves(ChessBoard *chessBoard, char color);   
  vector<vector<Position>> get_attacking_moves(ChessBoard *chessBoard, vector<vector<Position>> moves);
  vector<vector<Position>> get_escaping_moves(ChessBoard *chessBoard, vector<vector<Position>> moves);
  vector<vector<Position>> get_check_moves(ChessBoard *chessBoard, vector<vector<Position>> moves);
  vector<vector<Position>> get_checkmate_moves(ChessBoard *chessBoard, vector<vector<Position>> moves);
  int num_of_attackable_pieces(ChessBoard *chessBoard);
public:
  virtual ~Computer() = default;
  virtual vector<Position> play(ChessBoard *chessBoard) = 0;
};

#endif
