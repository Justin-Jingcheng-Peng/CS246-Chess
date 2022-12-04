#include "computerPlayer.h"
#include "chessBoard.h"
#include "position.h"
#include <string>
#include <vector>
#include <random>

using namespace std;

// Gets a vector/"array" of moves (in the form of position) that follow the rules of chess
vector<vector<Position>> ComputerPlayer::get_moves(ChessBoard *chessBoard, char color) {
  vector<vector<Position>> moves;
  vector<vector<shared_ptr<Piece>>> theBoard = chessBoard->get_board();
  
}