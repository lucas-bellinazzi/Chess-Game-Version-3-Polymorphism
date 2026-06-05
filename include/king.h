#ifndef KING_H
#define KING_H

#include <iostream>
#include <string>
#include "piece.h"

class Board;

class King: public Piece
{
public:
	bool validateMove(int final_row, int final_col, Board *board) override;	

	std::string toString() override { 

		if(getColor() == 'B') return "\u265B";
		else return "\u2655"; 
	}
};

#endif
