#ifndef BISHOP_H
#define BISHOP_H

#include <iostream>
#include <string>
#include "piece.h"

class Board;

class Bishop: public Piece
{
public:	
	// Function responsible for verifying if the move is valid
	bool validateMove(int final_row, int final_col, Board *board) override;

	std::string toString() override { 

		if(getColor() == 'B') return "\u265D";
		else return "\u2654"; 
	}

private:
	int pieceInPath(int current_row, int current_col, int final_row, int final_col, Board *board);	
};

#endif
