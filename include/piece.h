#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>

class Board;

class Piece
{
public:
	virtual bool validateMove(int final_row, int final_col, Board *board) = 0;
	void initializePosition(int r, int c)
	{
		_row = r;
		_col = c;
		return;
	}
	void setMovesCount() { movesCount++; }
	int getMovesCount() { return movesCount; }
	int getCurrentRow() { return _row; }
	int getCurrentColumn() { return _col; }
	void incrementMovesCount() { movesCount++; }
	void setColor(char c) { color = c; }
	char getColor() { return color; }

	virtual std::string toString() = 0;

private:
	int movesCount = 0;
	int _row;
	int _col; // current position in row and col
	char color;
};

#endif
