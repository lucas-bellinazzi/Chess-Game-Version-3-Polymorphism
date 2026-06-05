#ifndef ROOK_H
#define ROOK_H

#include <iostream>
#include <string>
#include "piece.h"

class Board;

class Rook: public Piece
{
public:	
	bool validateMove(int final_row, int final_col, Board *board) override;
	bool isChecking(int n, int m);

	std::string toString() override { 

		if(getColor() == 'B') return "\u265C";
		else return "\u2656"; 
	}

private:	
	int pieceInPath(int current_row, int current_col, int final_row, int final_col, Board *board);		
};

#endif
