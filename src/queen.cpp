#include <iostream>
#include <string>

#include "board.h"
#include "queen.h"

bool Queen::validateMove( int final_row, int final_col, Board *board)
{
	// Verifying if destination is valid for rook-like movement
	if( getCurrentRow() == final_row || getCurrentColumn() == final_col )
	{
		// Verifying if there is any piece in the path
		if(pieceInPathRook(getCurrentRow(), getCurrentColumn(), final_row, final_col, board) == 0)
		{
			board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
			board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
			initializePosition(final_row, final_col);
			return true;
	    }
  	}

    // Verifying if destination is valid for bishop-like movement
	if( (final_col - final_row) == (getCurrentColumn() - getCurrentRow()) ||  (final_col + final_row) == (getCurrentColumn() + getCurrentRow()) )
	{
		// Verifying if there is any piece in the path
		if(pieceInPathBishop(getCurrentRow(), getCurrentColumn(), final_row, final_col, board) == 0)
		{
			board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
			board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
			initializePosition(final_row, final_col);
			return true;
		}
		return false;
	}

	else return false;
}

int Queen::pieceInPathRook(int current_row, int current_col, int final_row, int final_col, Board *board)
{
	if(current_row == final_row && current_col == final_col) return 1;

	if(current_row == final_row && current_col > final_col) // Case 1: moving straight left
	{
		int i = current_row;
		int j = current_col-1;

		while(j > final_col)
		{			
			if(board->getPieceAt(i, j) != nullptr)
			{
				return 1;
			}
			j--;
		}
		return 0;
	}

	if(current_row == final_row && current_col < final_col) // Case 2: moving straight right
	{
		int i = current_row;
		int j = current_col+1;	

		while(j < final_col)
		{			
			if(board->getPieceAt(i, j) != nullptr)
			{				
				return 1;
			}
			j++;
		}

		return 0;	
	}

	if(current_row < final_row && current_col == final_col) // Case 3: moving straight down
	{
		int i = current_row+1;
		int j = current_col;
		while(i < final_row)
		{			
			if(board->getPieceAt(i, j) != nullptr)
			{
				return 1;
			}
			i++;
		}
		return 0;
	}

	if(current_row > final_row && current_col == final_col) // Case 4: moving straight up
	{
		int i = current_row-1;
		int j = current_col;
		while(i > final_row)
		{			
			if(board->getPieceAt(i, j) != nullptr)
			{
				return 1;
			}
			i--;
		}
		return 0;
	}

	return 0;
}	


int Queen::pieceInPathBishop(int current_row, int current_col, int final_row, int final_col, Board *board)
{
  	if(current_row == final_row && current_col == final_col) return 1;

	if(current_row > final_row && current_col > final_col) // Case 1: moving up-left
	{
		int i = current_row-1;
		int j = current_col-1;

		while(i > final_row && j > final_col)
		{			
			if(board->getPieceAt(i, j) != nullptr)
			{
		    	return 1;
			}
			i--;
			j--;
		}
		return 0;
	}

	if(current_row > final_row && current_col < final_col) // Case 2: moving up-right
	{
		int i = current_row-1;
		int j = current_col+1;

		while(i > final_row && j < final_col)
		{			
			if(board->getPieceAt(i, j)!= nullptr)
			{
		    	return 1;
			}
			i--;
			j++;
		}
		return 0;
	}

	if(current_row < final_row && current_col < final_col) // Case 3: moving down-right
	{
		int i = current_row+1;
		int j = current_col+1;

		while(i < final_row && j < final_col)
		{			
			if(board->getPieceAt(i, j)!= nullptr)
			{
	    		return 1;
			}
			i++;
			j++;
		}
		return 0;
	}

	if(current_row < final_row && current_col > final_col) // Case 4: moving down-left
	{
		int i = current_row+1;
		int j = current_col-1;

		while(i < final_row && j > final_col)
		{			
			if(board->getPieceAt(i, j)!= nullptr)
			{
				return 1;
			}
			i++;
			j--;
		}
		return 0;
	}
	
	return 0;	
}
