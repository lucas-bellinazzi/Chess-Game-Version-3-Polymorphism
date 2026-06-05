#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include <string>
#include <cmath>
#include "piece.h"

class Board;

class Knight: public Piece
{
public:
	/*	VALIDATE_MOVE
	 *		Receives as parameters two integers representing row and col positions (respectively) on the board and a pointer to the board.
	 *		Returns a logical value (true or false) indicating if the requested move is valid.
	 */
	bool validateMove(int final_row, int final_col, Board *board) override;

	std::string toString() override { 

		if(getColor() == 'B') return "\u265E"; // Black Knight
		else return "\u2658"; // White Knight
	}
};

#endif
