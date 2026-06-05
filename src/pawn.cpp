#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;
#include "board.h"
#include "pawn.h"

bool Pawn::validateMove( int final_row, int final_col, Board *board)
{

   char cor = board->getPieceAt(getCurrentRow(), getCurrentColumn())->getColor();

   // PAWN CAPTURE
   if( board->getPieceAt(final_row, final_col)!=nullptr && board->getPieceAt(final_row, final_col)->getColor()!=cor && abs(final_row-getCurrentRow())==1 && abs(final_col-getCurrentColumn())==1 )
   {
   	  if( abs(final_row-getCurrentRow()) == 2 ) movedTwoSquares = true;
   	  else movedTwoSquares = false;

      board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
      board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
      initializePosition(final_row, final_col);
      incrementMovesCount();
      return true;
   }

   // BLACK PIECES (B)
   if(cor=='B')
   {
      if( final_row==getCurrentRow()+1 && getCurrentColumn()==final_col )
      {
         if(pieceInPath(getCurrentRow(),getCurrentColumn(), final_row, final_col, board) == 0)
         {

         	if( abs(final_row-getCurrentRow()) == 2 ) movedTwoSquares = true;
   	  		else movedTwoSquares = false;

            board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
            board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
            initializePosition(final_row, final_col);
            incrementMovesCount();
            return true;
         }
      }

      else if( final_row==getCurrentRow()+2 && getCurrentColumn()==final_col && getMovesCount()==0)
      {
         if(pieceInPath(getCurrentRow(),getCurrentColumn(), final_row, final_col, board) == 0)
         {
         	if( abs(final_row-getCurrentRow()) == 2 ) movedTwoSquares = true;
   	  		else movedTwoSquares = false;

            board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
            board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
            initializePosition(final_row, final_col);
            incrementMovesCount();
            return true;
         }
      }
      return false;
   }
   // WHITE PIECES (W)
   else if(cor == 'W')
   {
      if( final_row==getCurrentRow()-1 && getCurrentColumn()==final_col )
      {
         if(pieceInPath(getCurrentRow(),getCurrentColumn(), final_row, final_col, board) == 0)
         {
         	if( abs(final_row-getCurrentRow()) == 2 ) movedTwoSquares = true;
   	  		else movedTwoSquares = false;

            board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
            board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
            initializePosition(final_row, final_col);
            incrementMovesCount();
            return true;
         }
      }

      else if( final_row==getCurrentRow()-2 && getCurrentColumn()==final_col && getMovesCount()==0)
      {
         if(pieceInPath(getCurrentRow(),getCurrentColumn(), final_row, final_col, board) == 0)
         {
         	if( abs(final_row-getCurrentRow()) == 2 ) movedTwoSquares = true;
   	  		else movedTwoSquares = false;
   	  		
            board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
            board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
            initializePosition(final_row, final_col);
            incrementMovesCount();
            return true;
         }
      }
      return false;
   }
   return false;
}


int Pawn::pieceInPath(int current_row, int current_col, int final_row, int final_col, Board *board)
{
   int x = current_col;
   volatile int y = current_row;

   int valor;
   if(final_row > y) valor = 1;
   else valor = -1;

   if(board->getPieceAt(final_row, final_col)!=  nullptr && current_col==final_col)
   {
      return 1;
   }

   y += valor;
   while(y != final_row)
   {

      if(board->getPieceAt(y, x)!= nullptr)
         return 1;

      y += valor;
   }
   return 0;
}
