#include "graphicsObserver.h"
#include "observer.h"
#include "chessBoard.h"
#include "piece.h"
#include "move.h"
#include "window.h"
#include <memory>
#include <string>

using namespace std;

GraphicsObserver::GraphicsObserver(ChessBoard *chessBoard) : 
chessBoard{chessBoard}, 
window{make_shared<Xwindow>(480, 480)} {
  chessBoard->attach(this);
}

GraphicsObserver::~GraphicsObserver() {
  chessBoard->detach(this);
}

void GraphicsObserver::notify(string gameResult) {
  if (gameResult == "sr") return;

  vector<vector<shared_ptr<Piece>>> chessBoardVector = chessBoard->get_board();
  if (chessBoard->get_mode() == "setup"
  || chessBoard->get_num_moves() == 0
  || gameResult[0] == 'u') {
    for (int i = 8; i > 0; i--) {
      window->drawString(25, 25 + 50 * abs(i - 8), to_string(i));
    }
  
    char c = 'a';
    for (int i = 75; i <= 425; i+= 50) {
      string s;
      s += c;
      window->drawString(i, 420, s);
      c++;
    }
  
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        
        if (isRed) {
          window->fillRectangle(430, 430, 50, 50, 1);
          isRed = false;
        }
        else {
          window->fillRectangle(430, 430, 50, 50, 1);
          isRed = true;
        }
  
        if (chessBoardVector[i][j] == nullptr) {
          if ((i+j) % 2 == 1) {window->fillRectangle(50 + j * 50, i * 50, 50, 50, 8);}
          else {
            window->fillRectangle(50 + j * 50, i * 50, 50, 50, 9);}
        }
        else {
          string st;
          st += chessBoardVector[i][j]->get_symbol();
          window->fillRectangle(50 + j * 50, i * 50, 50, 50, 0);
          window->drawString(75 + j * 50, 25 + i * 50, st);
        }
  
        window->drawString(100, 455, "Please wait, the chessboard is being updated");
      }
    }
  
    window->fillRectangle(100, 430, 250, 50, 0);
  }

  else {
    // x starts from left as 0
    // y starts from top as 0
    // orig is from, final is to
    Move recentMove = chessBoard->get_last_move();
    Position orig = recentMove.get_orig_pos();
    Position final_pos = recentMove.get_final_pos();

    int orig_x = from.get_x_pos();
    int orig_y = from.get_y_pos();
    if ((orig_x % 2 == 0) && (orig_y % 2 == 0)) {
      // print white square
      window->fillRectangle(orig_x * 50 + 50, orig_y * 50, 50, 50, 8);
    } else if ((orig_x % 2 == 0) && (orig_y % 2 != 0)) {
      // print black square
      window->fillRectangle(orig_x * 50 + 50, orig_y * 50, 50, 50, 9);
    } else if ((orig_x % 2 != 0) && (orig_y % 2 == 0)) {
      window->fillRectangle(orig_x * 50 + 50, orig_y * 50, 50, 50, 9);
    } else {
      window->fillRectangle(orig_x * 50 + 50, orig_y * 50, 50, 50, 8);
    }
    // add piece to final pos position.
    string st;
    st += (recentMove.get_piece())->get_symbol();
    window->fillRectangle(final_pos.get_x_pos() * 50 + 50, final_pos.get_y_pos() * 50, 50, 50, 0);
    window->drawString(final_pos.get_x_pos() * 50 + 75, final_pos.get_y_pos() * 50 + 25, st);

    if (recentMove.get_enpassant()) {
      int move_unit = ((recentMove.get_piece())->get_color() == 'w') ? -1 : 1;
      int p_x = recentMove.get_final_pos().get_x_pos();
      int p_y = recentMove.get_final_pos().get_y_pos();
      if ((p_x + p_y) % 2 == 1) {
        window->fillRectangle(p_x * 50 + 50, p_y * 50, 50, 50, 9);
      } else {
        window->fillRectangle(p_x * 50 + 50, p_y * 50, 50,  50, 8);
      }
    }
    if (recentMove.get_castling()) {
      if (recentMove.get_final_pos().get_x_pos() == 6 && recentMove.get_final_pos().get_y_pos() == 7) {
        window->fillRectangle(5 * 50 + 50, 7 * 50, 50, 50, 0);
        window->drawString(5 * 50 + 75, 7 * 50 + 25, "R");
        window->fillRectangle(7 * 50 + 50, 7 * 50, 50, 50, 8);
      }
      if (recentMove.get_final_pos().get_x_pos() == 2 && recentMove.get_final_pos().get_y_pos() == 7) {
        window->fillRectangle(3 * 50 + 50, 7 * 50, 50, 50, 0);
        window->drawString(3 * 50 + 75, 7 * 50 + 25, "R");
        window->fillRectangle(0 * 50 + 50, 7 * 50, 50, 50, 9);
      }
      if (recentMove.get_final_pos().get_x_pos() == 6 && recentMove.get_final_pos().get_y_pos() == 0) {
        window->fillRectangle(5 * 50 + 50, 0 * 50, 50, 50, 0);
        window->drawString(5 * 50 + 75, 0 * 50 + 25, "r");
        window->fillRectangle(7 * 50 + 50, 0 * 50, 50, 50, 9);
      }
      if (recentMove.get_final_pos().get_x_pos() == 2 && recentMove.get_final_pos().get_y_pos() == 0) {
        window->fillRectangle(3 * 50 + 50, 0 * 50, 50, 50, 0);
        window->drawString(3 * 50 + 75, 0 * 50 + 25, "r");
        window->fillRectangle(0 * 50 + 50, 0 * 50, 50, 50, 8);
      }
    }

    // promotion
    if ((chessBoardVector[recentMove.get_final_pos().get_y_pos()][recentMove.get_final_pos().get_x_pos()]->get_color() == 'w' && recentMove.get_final_pos().get_y_pos() == 0) || (chessBoardVector[recentMove.get_final_pos().get_y_pos()][recentMove.get_final_pos().get_x_pos()]->get_color() == 'b' && recentMove.get_final_pos().get_y_pos() == 7)) {
      if (chessBoardVector[recentMove.get_final_pos().get_y_pos()][recentMove.get_final_pos().get_x_pos()]->get_color() == 'w') {
        window->fillRectangle(recentMove.get_final_pos().get_x_pos() * 50 + 50, recentMove.get_final_pos().get_y_pos() * 50, 50, 50, 0);
        window->drawString(recentMove.get_final_pos().get_x_pos() * 50 + 75, recentMove.get_final_pos().get_y_pos()* 50 + 25, "Q");
      } else {
        window->fillRectangle(recentMove.get_final_pos().get_x_pos() * 50 + 50, recentMove.get_final_pos().get_y_pos() * 50, 50, 50, 0);
        window->drawString(recentMove.get_final_pos().get_x_pos() * 50 + 75, recentMove.get_final_pos().get_y_pos()* 50 + 25, "q");
      }
    }
  }
}
