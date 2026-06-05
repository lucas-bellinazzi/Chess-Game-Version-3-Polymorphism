#include "board.h"
#include "king.h"
#include "rook.h"

bool King::validateMove( int final_row, int final_col, Board *board)
{
	Piece *peca_alvo = board->getPieceAt(final_row, final_col);
	if (board->isBlackKing(peca_alvo) || board->isBlackKing(peca_alvo)) {return false;} // Condition to prevent King from capturing other King
	

	if ((getCurrentRow() -1 == final_row && getCurrentColumn() == final_col )|| ( getCurrentRow() -1 == final_row && getCurrentColumn()+1 == final_col )|| (getCurrentRow() -1 == final_row && getCurrentColumn()-1 == final_col)){
			board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
			board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
			initializePosition(final_row, final_col);
			incrementMovesCount();
			return true;
	}

	if ((getCurrentRow() +1 == final_row && getCurrentColumn()+1 == final_col ) || (getCurrentRow() +1 == final_row && getCurrentColumn() == final_col) || (getCurrentRow() +1 == final_row && getCurrentColumn()-1 == final_col)){
			board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
			board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
			initializePosition(final_row, final_col);
			incrementMovesCount();
			return true;
	}

	if ((getCurrentRow() == final_row && getCurrentColumn()+1 == final_col ) || (getCurrentRow() == final_row && getCurrentColumn()-1 == final_col) ){
			board->setPieceAt(final_row, final_col, board->getPieceAt(getCurrentRow(), getCurrentColumn()));
			board->setPieceAt(getCurrentRow(), getCurrentColumn(), nullptr);
			initializePosition(final_row, final_col);
			incrementMovesCount();
	    	return true;
	}
	
	return false;
}
