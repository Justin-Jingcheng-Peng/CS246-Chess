#include "chessBoard.h"
#include "position.h"
#include <string>

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

  this->round = 'w';
  for (int r = 0; r < 8; r++)
  {
    for (int c = 0; c < 8; c++)
    {
      this->board[r][c] = nullptr;
    }
  }
  this->setNewPiece(0, 0, 'r');
  this->setNewPiece(0, 1, 'n');
  this->setNewPiece(0, 2, 'b');
  this->setNewPiece(0, 3, 'q');
  this->setNewPiece(0, 4, 'k');
  this->setNewPiece(0, 5, 'b');
  this->setNewPiece(0, 6, 'n');
  this->setNewPiece(0, 7, 'r');

  this->setNewPiece(1, 0, 'p');
  this->setNewPiece(1, 1, 'p');
  this->setNewPiece(1, 2, 'p');
  this->setNewPiece(1, 3, 'p');
  this->setNewPiece(1, 4, 'p');
  this->setNewPiece(1, 5, 'p');
  this->setNewPiece(1, 6, 'p');
  this->setNewPiece(1, 7, 'p');

  this->setNewPiece(6, 0, 'P');
  this->setNewPiece(6, 1, 'P');
  this->setNewPiece(6, 2, 'P');
  this->setNewPiece(6, 3, 'P');
  this->setNewPiece(6, 4, 'P');
  this->setNewPiece(6, 5, 'P');
  this->setNewPiece(6, 6, 'P');
  this->setNewPiece(6, 7, 'P');

  this->setNewPiece(7, 0, 'R');
  this->setNewPiece(7, 1, 'N');
  this->setNewPiece(7, 2, 'B');
  this->setNewPiece(7, 3, 'Q');
  this->setNewPiece(7, 4, 'K');
  this->setNewPiece(7, 5, 'B');
  this->setNewPiece(7, 6, 'N');
  this->setNewPiece(7, 7, 'R');
}
// dtor
ChessBoard::~ChessBoard()
{
  // dtor is is responsible for cleaning up the past history pointers and pointers in the current board 2D vector
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      delete this->board[x][y];
    }
  }
  // clean up the history.
  while (this->pastMoves.size() > 0)
  {
    Move temp = this->pastMoves.back();
    delete temp.removed_piece;
    this->pastMoves.pop_back();
  }
}
// Get a copy of the piece ptr;
Piece *ChessBoard::getPieceAt(int x, int y)
{
  return this->board[x][y];
}
// Get the copy of the 2D vector
std::vector<std::vector<Piece *>> ChessBoard::get_board()
{
  return this->board;
}
// get a copy of the last move
Move ChessBoard::get_last_move()
{
  return pastMoves.back();
}
// Given a position, return true if this position is within the chessboard bound, false otherwise
bool ChessBoard::isInBound(Position p1)
{
  if (p1.get_x_pos() >= 0 && p1.get_x_pos() <= 7)
  {
    if (p1.get_y_pos() >= 0 && p1.get_y_pos() <= 7)
    {
      return true;
    }
  }
  return false;
}
// Given a position, return true if this position is both in bound and this position has a piece (non empty).
bool ChessBoard::isInBoundAndNonNull(Position p1)
{
  return (this->isInBound(p1) && this->board[p1.get_x_pos()][p1.get_y_pos()] != nullptr);
}
// Take two postions. Do a normal move. There are two types. 1) Move from one Position to another empty cell. 2) Move from one Position to eat the opponent's piece.
void ChessBoard::standardMove(Position initPos, Position finalPos)
{
  this->move(initPos, finalPos, false);
}
// This is an internal function that is has a lot of logic in it. Thus this is private.
void ChessBoard::move(Position initPos, Position finalPos, bool is_castling)
{
  const int init_row = initPos.get_x_pos();
  const int init_col = initPos.get_y_pos();
  const int fin_row = finalPos.get_x_pos();
  const int fin_col = finalPos.get_y_pos();
  // Validility check
  // Check if the starting postion is null(empty);

  if (this->board[init_row][init_col] == nullptr)

  {
    cout << "Invalid move. There is no Piece in this position" << endl;
    return;
  }
  // Check boundary;
  if (isInBound(initPos) == false || isInBound(finalPos) == false)
  {
    cout << "Invalid move! This move is out of the bound!" << endl;
    return;
  }
  // // Check if white eats white or black eats black;

  if (this->board[fin_row][fin_col] != nullptr)
  {
    if ((this->board[fin_row][fin_col]->get_color() == 'w' && this->board[init_row][init_col]->get_color() == 'w') || (this->board[fin_row][fin_col]->get_color() == 'b' && this->board[init_row][init_col]->get_color() == 'b'))
    {
      cout << "Invalid move! This makes one color to eat the same color" << endl;
      return;
    }
  }
  // Color check;
  if ((this->round == 'b' && this->board[init_row][init_col]->get_color() == 'w') || (this->round == 'w' && this->board[init_row][init_col]->get_color() == 'b'))
  {
    cout << "Invalid move! Wrong color!" << endl;
    return;
  }

  // The case that no pieces are eaten, do a simple move
  if (this->board[fin_row][fin_col] == nullptr)
  {
    Piece *temp = this->board[init_row][init_col];
    this->board[init_row][init_col] = nullptr;
    this->board[fin_row][fin_col] = temp;
    if (is_castling == false)
    {
      this->pastMoves.push_back(Move{nullptr, Position{init_row, init_col}, Position{fin_row, fin_col}, false, false, false});
    }
    else
    {
      this->pastMoves.push_back(Move{nullptr, Position{init_row, init_col}, Position{fin_row, fin_col}, true, false, false});
    }
  }
  // The case that the final position has a piece from the opponent, we delete the opponent and move it there
  else
  {

    if ((this->board[fin_row][fin_col]->get_color() == 'w' && this->board[init_row][init_col]->get_color() == 'b') || (this->board[fin_row][fin_col]->get_color() == 'b' && this->board[init_row][init_col]->get_color() == 'w'))
    {

      Piece *removedPiece = this->board[fin_row][fin_col];
      Piece *temp = this->board[init_row][init_col];
      this->board[init_row][init_col] = nullptr;
      this->board[fin_row][fin_col] = temp;

      this->pastMoves.push_back(Move{removedPiece, Position{init_row, init_col}, Position{fin_row, fin_col}, false, false, false});
    }
    else
    {
      cout << "Invalid Move! This move is out of the bound!" << endl;
      return;
    }
  }
  if (this->round == 'b')
  {
    this->round = 'w';
  }
  else
  {
    this->round = 'b';
  }
}
// Taking a direction and the color, move the castling. Note: This function is very weak so make sure that the current board meet the castling critiria before you preceed.
void ChessBoard::castlingMove(char direction, char color)
{

  if (direction == 'l' && color == 'w')
  {
    // We split a castling into two moves. In pastMoves vector, we mark the second movement as the end of this "move" combination;
    this->move(Position{7, 4}, Position{7, 2}, false);
    this->round = 'w';
    this->move(Position{7, 0}, Position{7, 3}, true);
  }
  else if (direction == 'r' && color == 'w')
  {
    this->move(Position{7, 4}, Position{7, 6}, false);
    this->round = 'w';
    this->move(Position{7, 7}, Position{7, 5}, true);
  }
  else if (direction == 'l' && color == 'b')
  {
    this->move(Position{0, 4}, Position{0, 2}, false);
    this->round = 'b';
    this->move(Position{0, 0}, Position{0, 3}, true);
  }
  else if (direction == 'r' && color == 'b')
  {
    this->move(Position{0, 4}, Position{0, 6}, false);
    this->round = 'b';
    this->move(Position{0, 7}, Position{0, 5}, true);
  }
}
// Take three positions: Initial position, final position, and the position of the eaten piece. Process an enpassant move.
void ChessBoard::enpassantMove(Position initPos, Position finalPos, Position eatenPiecePosition)
{
  const int init_row = initPos.get_x_pos();
  const int init_col = initPos.get_y_pos();
  const int fin_row = finalPos.get_x_pos();
  const int fin_col = finalPos.get_y_pos();
  // First move the pawn from the init_postion to the final, no pieces got eaten
  Piece *temp = this->board[init_row][init_col];
  this->board[init_row][init_col] = nullptr;
  this->board[fin_row][fin_col] = temp;
  this->pastMoves.push_back(Move{nullptr, Position{init_row, init_col}, Position{fin_row, fin_col}, false, false, false});
  // Then the piece got eaten
  temp = this->board[eatenPiecePosition.x][eatenPiecePosition.y];
  this->board[eatenPiecePosition.x][eatenPiecePosition.y] = nullptr;
  this->pastMoves.push_back(Move{temp, Position{eatenPiecePosition.x, eatenPiecePosition.y}, Position{eatenPiecePosition.x, eatenPiecePosition.y}, false, true, false});
  if (this->round == 'b')
  {
    this->round = 'w';
  }
  else
  {
    this->round = 'b';
  }
}
// Brute force implementation, find all possible ways the black king can be checked.
void ChessBoard::promotionMove(Position initPos, Position finalPos, char pieceTurnedTo)
{
  delete this->board[initPos.x][initPos.y];
  Piece *temp = this->board[finalPos.x][finalPos.y];
  this->setNewPiece(finalPos.x, finalPos.y, pieceTurnedTo);
  this->board[initPos.x][initPos.y] = nullptr;
  this->pastMoves.push_back(Move{temp, initPos, finalPos, false, false, true});
  if (this->round == 'b')
  {
    this->round = 'w';
  }
  else
  {
    this->round = 'b';
  }
}
bool ChessBoard::isBlackBeingChecked()
{

  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      // find the black king
      if (this->board[x][y] != nullptr && this->board[x][y]->get_symbol() == 'k')
      {

        // check pawn capture;
        if ((isInBoundAndNonNull(Position{x + 1, y - 1}) && this->board[x + 1][y - 1]->get_symbol() == 'P') || (isInBoundAndNonNull(Position{x + 1, y + 1}) && this->board[x + 1][y + 1]->get_symbol() == 'P'))
        {
          return true;
        }
        // check the knight capture;
        if ((isInBoundAndNonNull(Position{x - 2, y - 1}) && this->board[x - 2][y - 1]->get_symbol() == 'N') || (isInBoundAndNonNull(Position{x - 1, y - 2}) && this->board[x - 1][y - 2]->get_symbol() == 'N') || (isInBoundAndNonNull(Position{x + 1, y - 2}) && this->board[x + 1][y - 2]->get_symbol() == 'N') || (isInBoundAndNonNull(Position{x + 2, y - 1}) && this->board[x + 2][y - 1]->get_symbol() == 'N') || (isInBoundAndNonNull(Position{x + 2, y + 1}) && this->board[x + 2][y + 1]->get_symbol() == 'N') || (isInBoundAndNonNull(Position{x + 1, y + 2}) && this->board[x + 1][y + 2]->get_symbol() == 'N') || (isInBoundAndNonNull(Position{x - 2, y + 1}) && this->board[x - 2][y + 1]->get_symbol() == 'N') || (isInBoundAndNonNull(Position{x - 1, y + 2}) && this->board[x - 1][y + 2]->get_symbol() == 'N'))
        {
          return true;
        }
        // check the bishop;
        Position p1{x, y};
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x++;
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'B')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x++;
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'B')
          {
            return true;
          }

          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x--;
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'B')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))

        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x--;
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'B')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        // Check Queen capturing:
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x++;
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'Q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x++;
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'Q')
          {
            return true;
          }

          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x--;
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'Q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x--;
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'Q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'Q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'Q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'Q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'Q')
          {
            return true;
          }
          else
          {
            break;
          }
        }

        // Check rook capture;
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'R')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.x++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'R')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'R')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'k')
          {
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'R')
          {
            return true;
          }
          else
          {
            break;
          }
        }
      }
    }
  }
  return false;
}
// This function is not tested at all since this function rely on the implementation of pieces' method
bool ChessBoard::isBlackLost()
{
  // The game does not allow direct capture of King
  if (this->round == 'w')
  {
    return false;
  }

  /*
  Approach: When the black is in check and black has no legal moving postion.
  */
  int count = 0;
  if (this->isBlackBeingChecked() == true)
  {
    for (int x = 0; x < 8; x++)
    {
      for (int y = 0; y < 8; y++)
      {
        if (this->board[x][y] != nullptr && this->board[x][y]->get_symbol() == 'K')
        {
          for (int i = 0; i < 8; i++)
          {
            for (int j = 0; j < 8; j++)
            {
              Position curPos = Position{x, y};
              Position targetPos = Position{i, j};
              if (this->board[x][y]->valid_move(this, curPos, targetPos))
              {
                count++;
              }
            }
          }
        }
      }
    }
    // (count == 0) implies that there is no legal moves;
    if (count == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  // If black is not checked, it means black is not losing.
  else
  {
    return false;
  }
}
// This function is not tested at all since this function rely on the implementation of pieces' method
bool ChessBoard::isWhiteLost()
{
  // The game does not allow direct capture of King
  if (this->round == 'b')
  {
    return false;
  }

  /*
  Approach: When the black is in check and black has no legal moving postion.
  */
  int count = 0;
  if (this->isBlackBeingChecked() == true)
  {
    for (int x = 0; x < 8; x++)
    {
      for (int y = 0; y < 8; y++)
      {
        if (this->board[x][y] != nullptr && this->board[x][y]->get_symbol() == 'k')
        {
          for (int i = 0; i < 8; i++)
          {
            for (int j = 0; j < 8; j++)
            {
              Position curPos = Position{x, y};
              Position targetPos = Position{i, j};
              if (this->board[x][y]->valid_move(this, curPos, targetPos))
              {
                count++;
              }
            }
          }
        }
      }
    }
    // (count == 0) implies that there is no legal moves;
    if (count == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  // If black is not checked, it means black is not losing.
  else
  {
    return false;
  }
}
// Brute force implementation, find all possible ways the black king can be checked.
bool ChessBoard::isWhiteBeingChecked()
{

  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      // find the white king
      if (this->board[x][y] != nullptr && this->board[x][y]->get_symbol() == 'K')
      {

        // check pawn capture;
        if ((isInBoundAndNonNull(Position{x - 1, y - 1}) && this->board[x - 1][y - 1]->get_symbol() == 'p') || (isInBoundAndNonNull(Position{x - 1, y + 1}) && this->board[x - 1][y + 1]->get_symbol() == 'p'))
        {
          return true;
        }
        // check the knight capture;
        if ((isInBoundAndNonNull(Position{x - 2, y - 1}) && this->board[x - 2][y - 1]->get_symbol() == 'n') || (isInBoundAndNonNull(Position{x - 1, y - 2}) && this->board[x - 1][y - 2]->get_symbol() == 'n') || (isInBoundAndNonNull(Position{x + 1, y - 2}) && this->board[x + 1][y - 2]->get_symbol() == 'n') || (isInBoundAndNonNull(Position{x + 2, y - 1}) && this->board[x + 2][y - 1]->get_symbol() == 'n') || (isInBoundAndNonNull(Position{x + 2, y + 1}) && this->board[x + 2][y + 1]->get_symbol() == 'n') || (isInBoundAndNonNull(Position{x + 1, y + 2}) && this->board[x + 1][y + 2]->get_symbol() == 'n') || (isInBoundAndNonNull(Position{x - 2, y + 1}) && this->board[x - 2][y + 1]->get_symbol() == 'n') || (isInBoundAndNonNull(Position{x - 1, y + 2}) && this->board[x - 1][y + 2]->get_symbol() == 'n'))
        {
          return true;
        }
        // check the bishop;
        Position p1{x, y};
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x++;
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'b')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x++;
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'b')
          {
            return true;
          }

          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x--;
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'b')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))

        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x--;
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'b')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        // Check Queen capturing:
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x++;
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x++;
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'q')
          {
            return true;
          }

          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x--;
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x--;
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'q')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'q')
          {
            return true;
          }
          else
          {
            break;
          }
        }

        // Check rook capture;
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'r')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.x++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'r')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.y--;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'r')
          {
            return true;
          }
          else
          {
            break;
          }
        }
        p1.x = x;
        p1.y = y;
        while (isInBound(p1))
        {
          if (this->board[p1.get_x_pos()][p1.get_y_pos()] == nullptr || this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'K')
          {
            p1.y++;
            continue;
          }
          if (this->board[p1.get_x_pos()][p1.get_y_pos()]->get_symbol() == 'r')
          {
            return true;
          }
          else
          {
            break;
          }
        }
      }
    }
  }
  return false;
}
// When either play lost, the game is finished;
bool ChessBoard::isGameFinish()
{
  return (this->isBlackLost() || this->isWhiteLost());
}
// Undo the moves
void ChessBoard::undo()
{
  Move prevMove = this->pastMoves.back();
  this->pastMoves.pop_back();
  this->board[prevMove.original_pos.x][prevMove.original_pos.y] = this->board[prevMove.final_pos.x][prevMove.final_pos.y];
  this->board[prevMove.final_pos.x][prevMove.final_pos.y] = prevMove.removed_piece;
  if (prevMove.is_castling == true)
  {
    this->undo();
  }
  else if (prevMove.is_enpassant == true)
  {
    this->undo();
  }
  else if (prevMove.is_promotion == true)
  {
    delete this->board[prevMove.original_pos.x][prevMove.original_pos.y];
    this->board[prevMove.original_pos.x][prevMove.original_pos.y] = nullptr;
    if (prevMove.original_pos.x == 1)
    {
      this->setNewPiece(prevMove.original_pos.x, prevMove.original_pos.y, 'P');
    }
    else
    {
      this->setNewPiece(prevMove.original_pos.x, prevMove.original_pos.y, 'p');
    }
    if (this->round == 'w')
    {
      this->round = 'b';
    }
    else
    {
      this->round = 'w';
    }
  }
  else
  {
    if (this->round == 'w')
    {
      this->round = 'b';
    }
    else
    {
      this->round = 'w';
    }
  }
}
// The method works as what its name says;
void ChessBoard::printBoardWithXYCordinates()
{
  cout << endl;
  for (int x = 0; x < 8; x++)
  {
    cout << x << "|";
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
  cout << "  ";
  cout << "0 1 2 3 4 5 6 7" << endl;
  cout << endl;
  cout << endl;
}
// The method works as what its name says;
void ChessBoard::printBoardWithStandardCordinates()
{
  cout << endl;
  for (int x = 0; x < 8; x++)
  {
    cout << x << "|";
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
  cout << "  ";
  cout << "a b c d e f g h" << endl;
  cout << endl;
  cout << endl;
}
// Set a new piece base on x,y values.
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
