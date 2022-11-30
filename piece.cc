#include "piece.h"
#include <iostream>
using namespace std; 
Piece::Piece(char symbol): symbol{symbol} {}
Piece::~Piece(){
  cout << "dtor called" << endl;
}
char Piece::get_symbol() {
  return this->symbol;
}

char Piece::get_type() {
  return this->symbol - 'a';
}

char Piece::get_color() {
  if (this->symbol >= 'a' && this->symbol <= 'z') {return 'b';}
  else {return 'w';}
}

// bool Piece::isKingChecked(){
//   // This method will only be overriden by King Piece.
//   // This method will never be called on other pieces.
//   return true;
// }