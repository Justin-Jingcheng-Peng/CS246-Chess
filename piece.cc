#include "piece.h"
#include <iostream>

using namespace std;

Piece::Piece(char symbol) : symbol{symbol}, move_count{0} {}

Piece::~Piece() {}

char Piece::get_symbol()
{
  return this->symbol;
}

char Piece::get_type()
{
  if (this->symbol < 'a') {return this->symbol - 'A' + 'a';}
  return this->symbol;
}

char Piece::get_color()
{
  if (this->symbol >= 'a' && this->symbol <= 'z')
  {
    return 'b';
  }
  else
  {
    return 'w';
  }
}

int Piece::get_move_count() {return move_count;}

void Piece::add_move_count() {move_count += 1;}

void Piece::sub_move_count() {move_count -= 1;}
