#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>
#include <string>
#include "piece.h"

class Board;

class Queen: public Piece
{
public:	
	bool validateMove(int final_row, int final_col, Board *board) override;
	
private:
	int pieceInPathRook(int current_row, int current_col, int final_row, int final_col, Board *board);
  	int pieceInPathBishop(int current_row, int current_col, int final_row, int final_col, Board *board);  

  	std::string toString() override { 

		if(getColor() == 'B') return "\u265A";
		else return "\u2654"; 
	}
};

#endif
