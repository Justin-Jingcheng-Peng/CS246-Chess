#include "computerPlayer.h"
#include "chessBoard.h"
#include "position.h"
#include <string>
#include <vector>
#include <random>
#include <memory>

using namespace std;

// Gets a vector/"array" of moves (in the form of position) that follow the rules of chess
vector<vector<Position>> ComputerPlayer::get_moves(ChessBoard *chessBoard, char color) {
  vector<vector<Position>> moves;
  vector<vector<shared_ptr<Piece>>> theBoard = chessBoard->get_board();

  char king = (color == 'b') ? 'k' : 'K';
  Position kingPosition = chessBoard->get_piece_pos(king);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (theBoard[i][j] != nullptr && theBoard[i][j]->get_color() == color) {
        for (int k = 0; k < 8; k++) {
          for (int l = 0; l < 8; l++) {
            if (theBoard[i][j]->valid_move(chessBoard, Position(j,i), Position(l,k))) {
              try {
                chessBoard->move(Position(j,i), Position(l,k), true);
              }

              catch (Error err) {
                throw;
              }
              
              if (!chessBoard->is_position_check(kingPosition, chessBoard->get_turn())) {
                moves.push_back({Position(j,i), Position(l,k)});
              }

              chessBoard->undo();
            }
          }
        }
      }
    }
  }
  
  return moves;
}

// Gets a vector/"array" of moves that can attack/capture an opponent's piece
vector<vector<Position>> ComputerPlayer::get_attacking_moves(ChessBoard *chessBoard, vector<vector<Position>> moves) {
  vector<vector<Position>> attackingMoves;
  vector<vector<shared_ptr<Piece>>> theBoard = chessBoard->get_board();

  int numOfMoves = moves.size();

  for (int i = 0; i < numOfMoves; i++) {
    // 0 is "from", 1 is "to"
    int x = moves[i][1].get_x_pos();
    int y = moves[i][1].get_y_pos();
    
    if (theBoard[y][x] != nullptr) {
      attackingMoves.emplace_back(moves[i]);
    }
  }

  return attackingMoves;
}

vector<vector<Position>> ComputerPlayer::get_escaping_moves(ChessBoard *chessBoard, vector<vector<Position>> moves) {
  vector<vector<Position>> escapingMoves;
  vector<vector<shared_ptr<Piece>>> theBoard = chessBoard->get_board();

  int numOfMoves = moves.size();
  int currNumOfAttackablePieces = num_of_attackable_pieces(chessBoard);
  for (int i = 0; i < numOfMoves; i++) {
    chessBoard->move(moves[i][0], moves[i][1], true);
    if (currNumOfAttackablePieces > num_of_attackable_pieces(chessBoard)) {
      escapingMoves.emplace_back(moves[i]);
    }

    chessBoard->undo();
  }

  return escapingMoves;
}

vector<vector<Position>> ComputerPlayer::get_check_moves(ChessBoard *chessBoard, vector<vector<Position>> moves) {
  vector<vector<Position>> checkMoves;
  vector<vector<shared_ptr<Piece>>> theBoard = chessBoard->get_board();

  int numOfMoves = moves.size();
  char king = (chessBoard->get_turn() == 'b' ? 'K' : 'k');
  char color = (chessBoard->get_turn() == 'b' ? 'w' : 'b');
  Position kingPosition = chessBoard->get_piece_pos(king);

  for (int i = 0; i < numOfMoves; i++) {
    chessBoard->move(moves[i][0], moves[i][1], true);
    if (chessBoard->is_position_check(kingPosition, color)) {
      checkMoves.emplace_back(moves[i]);
    }

    chessBoard->undo();
  }

  return checkMoves;
}

vector<vector<Position>> ComputerPlayer::get_checkmate_moves(ChessBoard *chessBoard, vector<vector<Position>> moves) {
  vector<vector<Position>> checkmateMoves;

  int numOfMoves = moves.size();
  
  string result = "";
  result += chessBoard->get_turn();
  result += "e";

  for (int i = 0; i < numOfMoves; i++) {
    chessBoard->move(moves[i][0], moves[i][1], true);
    if (result == chessBoard->check_board()) {
      checkmateMoves.emplace_back(moves[i]);
    }

    chessBoard->undo();
  }

  return checkmateMoves;
}

int ComputerPlayer::num_of_attackable_pieces(ChessBoard *chessBoard) {
  vector<vector<shared_ptr<Piece>>> theBoard = chessBoard->get_board();
  int num = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 0; j++) {
      if (theBoard[i][j] != nullptr && 
      (theBoard[i][j]->get_color() == chessBoard->get_turn()) && 
      theBoard[i][j]->get_type() == 'k' &&
      chessBoard->is_position_check(Position(j,i), chessBoard->get_turn())) {
        num++;
      }
    }
  }
  
  return num;
}

// Generates a random number n to get the nth element of a vector/array of moves
int ComputerPlayer::randomizer(int a, int b) {
  random_device d;
  mt19937 rng(d());
  uniform_int_distribution<mt19937::result_type> dist(a, b - 1);
  return dist(rng);
}
