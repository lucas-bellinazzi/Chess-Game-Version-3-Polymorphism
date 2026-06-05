#include <iostream>
#include <string>
using namespace std;
#include "board.h"
#include "knight.h"

bool Knight::validateMove( int final_row, int final_col, Board *board)
{
   if( (abs(final_row-getCurrentRow())==2 && abs(final_col- getCurrentColumn())==1) || (abs(final_row-getCurrentRow())==1 && abs(final_col-getCurrentColumn())==2) )
   {
      board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
		board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
		initializePosition(final_row, final_col);
      return true;
   }
   return false;
}
