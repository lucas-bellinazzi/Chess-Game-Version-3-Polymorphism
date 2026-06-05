#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include <string>
#include "piece.h"

class Board;

class Pawn: public Piece
{
public:	
	bool validateMove(int final_row, int final_col, Board *board) override;	
	void setMovedTwoSquaresTrue() { movedTwoSquares = true; }
	void setMovedTwoSquaresFalse() { movedTwoSquares = false; }
	bool getMovedTwoSquares() { return movedTwoSquares; }

	std::string toString() override { 

		if(getColor() == 'B') return "\u265F";
		else return "\u2659"; 
	}
	
private:
	int pieceInPath(int current_row, int current_col, int final_row, int final_col, Board *board);
	bool movedTwoSquares = false; // indicates if the pawn moved two squares on its first move
};

#endif
