#include "chessBoard.h"
#include "position.h"

/*
Black: lowercase
White: uppercase

king: k;
root: r;
bishop: b;
queen: q;
knight: n;
pawn: p;
*/

// Chessboard Constructor, init the chessboard with the chess starting position
ChessBoard::ChessBoard() : board(8, vector<Piece *>(8, 0))
{
  for (int r = 0; r < 8; r++)
  {
    for (int c = 0; c < 8; c++)
    {
      this->board[r][c] = nullptr;
    }
  }
  this->board[0][0] = new Rook{'r'};
  this->board[0][1] = new Knight{'n'};
  this->board[0][2] = new Bishop{'b'};
  this->board[0][3] = new Queen{'q'};
  this->board[0][4] = new King{'k'};
  this->board[0][5] = new Bishop{'b'};
  this->board[0][6] = new Knight{'n'};
  this->board[0][7] = new Rook{'r'};

  this->board[1][0] = new Pawn{'p'};
  this->board[1][1] = new Pawn{'p'};
  this->board[1][2] = new Pawn{'p'};
  this->board[1][3] = new Pawn{'p'};
  this->board[1][4] = new Pawn{'p'};
  this->board[1][5] = new Pawn{'p'};
  this->board[1][6] = new Pawn{'p'};
  this->board[1][7] = new Pawn{'p'};

  this->board[6][0] = new Pawn{'P'};
  this->board[6][1] = new Pawn{'P'};
  this->board[6][2] = new Pawn{'P'};
  this->board[6][3] = new Pawn{'P'};
  this->board[6][4] = new Pawn{'P'};
  this->board[6][5] = new Pawn{'P'};
  this->board[6][6] = new Pawn{'P'};
  this->board[6][7] = new Pawn{'P'};

  this->board[7][0] = new Rook{'R'};
  this->board[7][1] = new Knight{'N'};
  this->board[7][2] = new Bishop{'B'};
  this->board[7][3] = new Queen{'Q'};
  this->board[7][4] = new King{'K'};
  this->board[7][5] = new Bishop{'B'};
  this->board[7][6] = new Knight{'N'};
  this->board[7][7] = new Rook{'R'};
}
// Get the copy of the 2D vector
std::vector<std::vector<Piece *>> ChessBoard::get_board()
{
  return this->board;
}
//
int ChessBoard::get_num_moves()
{
  return pastMoves.size();
}

Move ChessBoard::get_last_move()
{
  return pastMoves.back();
}

// Take two postions. Make the pointer at iniPos pointing to null and make the pointer at the final finalPos pointing at the initPos.
void ChessBoard::move(Position initPos, Position finalPos)
{
  const int init_row = initPos.get_x_pos();
  const int init_col = initPos.get_y_pos();
  const int fin_row = finalPos.get_x_pos();
  const int fin_col = finalPos.get_y_pos();

  // The case that no pieces are eaten, do a simple move
  if (this->board[fin_row][fin_col] == nullptr)
  {
    Piece *temp = this->board[init_row][init_col];
    this->board[init_row][init_col] = nullptr;
    this->board[fin_row][fin_col] = temp;
  }
  // The case that the final position has a piece from the opponent, we delete the opponent and move it there
  else
  {

    if ((this->board[fin_row][fin_col]->get_color() == 'w' && this->board[init_row][init_col]->get_color() == 'b') || (this->board[fin_row][fin_col]->get_color() == 'b' && this->board[init_row][init_col]->get_color() == 'w'))
    {
      // There is a bug here;

      delete this->board[fin_row][fin_col];

      Piece *temp = this->board[init_row][init_col];
      this->board[init_row][init_col] = nullptr;
      this->board[fin_row][fin_col] = temp;
    }
  }
}

Piece *ChessBoard::getPieceAt(int x, int y)
{
  return this->board[x][y];
}

int ChessBoard::isGameFinish()
{
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      if (getPieceAt(x, y)->get_symbol() == 'K')
      {
        // if (getPieceAt(x,y)->isKingChecked() == true){
        //   return 1;
        // }
        return 1;
      }
    }
  }
  return 0;
}

int ChessBoard::getLastMove()
{
  // return this->pastMoves.back();
  return 0;
}

void ChessBoard::printBoard()
{
  for (int x = 0; x < 8; x++)
  {
    cout << "|";
    for (int y = 0; y < 8; y++)
    {
      if (this->board[x][y] != nullptr)
      {
        cout << this->getPieceAt(x, y)->get_symbol() << "|";
      }
      else
      {
        cout << " |";
      }
    }
    cout << endl;
  }
  cout << endl;
}

/* Some functions for testing purpose */

void ChessBoard::setNewPiece(int x, int y, char symbol)
{
  if (symbol == 'P' || symbol == 'p')
  {
    Piece *newPiecePtr = new Pawn{symbol};
    this->board[x][y] = newPiecePtr;
  }
  else if (symbol == 'K' || symbol == 'k')
  {
    Piece *newPiecePtr = new King{symbol};
    this->board[x][y] = newPiecePtr;
  }
  else if (symbol == 'N' || symbol == 'n')
  {
    Piece *newPiecePtr = new Pawn{symbol};
    this->board[x][y] = newPiecePtr;
  }
  else if (symbol == 'R' || symbol == 'r')
  {
    Piece *newPiecePtr = new Rook{symbol};
    this->board[x][y] = newPiecePtr;
  }
  else if (symbol == 'B' || symbol == 'b')
  {
    Piece *newPiecePtr = new Pawn{symbol};
    this->board[x][y] = newPiecePtr;
  }
  else
  {
    Piece *newPiecePtr = new Queen{symbol};
    this->board[x][y] = newPiecePtr;
  }
}