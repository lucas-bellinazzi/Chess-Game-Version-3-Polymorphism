#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <cmath>

#include "knight.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "pawn.h"
#include "rook.h"

class Board {

public:
	// Initializing pieces on the board
	Board();

	bool isBlackKing(Piece *p) { return p == &_blackKing; }
	bool isWhiteKing(Piece *p) { return p == &_whiteKing; }

	Piece *getPieceAt(int row, int col) const { return _matrix[row][col]; }
	void setPieceAt(int row, int col, Piece *piece) { _matrix[row][col] = piece; }

	int letterToCol(char letter)
	{
		switch(letter)
		{
			case 'a': return 0;
			case 'b': return 1;
			case 'c': return 2;
			case 'd': return 3;
			case 'e': return 4;
			case 'f': return 5;
			case 'g': return 6;
			case 'h': return 7;
			default: return -1;
		}
		return -1;
	}

	int numberToRow(char number)
	{
		switch(number)
		{
			case '1': return 7;
			case '2': return 6;
			case '3': return 5;
			case '4': return 4;
			case '5': return 3;
			case '6': return 2;
			case '7': return 1;
			case '8': return 0;
			default: return -1;
		}
		return -1;
	}

	std::string pieceCharToString(char letter)
	{
		switch(letter)
		{
			case 'N': return std::string("N"); // Knight
			case 'R': return std::string("R"); // Rook
			case 'B': return std::string("B"); // Bishop
			case 'Q': return std::string("Q"); // Queen
			case 'K': return std::string("K"); // King
			default: return std::string("error");
		}
		return std::string("error");
	}

	void decodePreviousMove(char current_piece_color, std::string &prev_piece_name, int &prev_piece_row, int &prev_piece_col, std::string prev_move)
	{
		char prev_piece_color;

		if(current_piece_color == 'B') prev_piece_color = 'W'; // If current is Black (B), previous was White (W)
		else prev_piece_color = 'B';

		prev_piece_row = numberToRow(prev_move[1]);
		prev_piece_col = letterToCol(prev_move[0]);
		prev_piece_name = std::string("P") + char('1' + letterToCol(prev_move[0])) + prev_piece_color;
		return;
	}

	bool en_passant(std::string piece_name, int final_row, int final_col)
	{			
		// piece_name is in format P1B or P1W where 1 is any number from 1 to 8
		// final_row is the destination row of the pawn
		// final_col is the destination column of the pawn		
		std::string prev_piece_name;
		int prev_piece_row, prev_piece_col;

		std::string prev_move = moveHistory[moveHistory.size()-1]; // Gets the last move
		decodePreviousMove(piece_name[2], prev_piece_name, prev_piece_row, prev_piece_col, prev_move);

		// Getting the index of each pawn
		int number = piece_name[1] - '1';
		int prev_number = prev_piece_name[1] - '1';

		if(moveHistory.size() != 0) // Prevents segmentation fault
		{			
			if(prev_piece_name[0] == 'P' && piece_name[0] == 'P') // Verifying both are pawns
			{
				// Case for White capturing Black pawn
				if(prev_piece_name[2] == 'B' && _blackPawns[prev_piece_col].getMovedTwoSquares() == true) // If the pawn being captured moved two squares
				{
					if(_blackPawns[prev_piece_col].getCurrentRow() == 3 && final_row+1 == 3) // Standard row 5 in chess (0-indexed 3)
					{
						if(abs(final_row - _whitePawns[number].getCurrentRow()) == 2) _whitePawns[number].setMovedTwoSquaresTrue();
						else _whitePawns[number].setMovedTwoSquaresFalse();

						setPieceAt(final_row, final_col, getPieceAt(_whitePawns[number].getCurrentRow(), _whitePawns[number].getCurrentColumn()));
						setPieceAt(_whitePawns[number].getCurrentRow(), _whitePawns[number].getCurrentColumn(), nullptr);
						setPieceAt(_blackPawns[prev_number].getCurrentRow(), _blackPawns[prev_number].getCurrentColumn(), nullptr);
						_whitePawns[number].initializePosition(final_row, final_col);
						_whitePawns[number].incrementMovesCount();            
						return true;
					}
					else return false;
				}

				// Case for Black capturing White pawn
				else if(prev_piece_name[2] == 'W' && _whitePawns[prev_piece_col].getMovedTwoSquares() == true) // If the pawn being captured moved two squares
				{
					if(_whitePawns[prev_piece_col].getCurrentRow() == 4 && final_row-1 == 4) // Standard row 4 in chess (0-indexed 4)
					{
						if(abs(final_row - _blackPawns[number].getCurrentRow()) == 2) _blackPawns[number].setMovedTwoSquaresTrue();
						else _blackPawns[number].setMovedTwoSquaresFalse();

						setPieceAt(final_row, final_col, getPieceAt(_blackPawns[number].getCurrentRow(), _blackPawns[number].getCurrentColumn()));
						setPieceAt(_blackPawns[number].getCurrentRow(), _blackPawns[number].getCurrentColumn(), nullptr);
						setPieceAt(_whitePawns[prev_number].getCurrentRow(), _whitePawns[prev_number].getCurrentColumn(), nullptr);
						_blackPawns[number].initializePosition(final_row, final_col);
						_blackPawns[number].incrementMovesCount();            
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}

	bool castle(int final_row, int final_col, char piece_type);

	bool isBlackKingInCheck(int n, int m);

	bool isWhiteKingInCheck(int n, int m);

	bool move(const std::string& piece_name, int final_row, int final_col, std::string move_str);

	std::vector<std::string> getMoveHistory() { return moveHistory; }

private:
	// matrix = chess board representation
	Piece *_matrix[8][8];

	std::vector<std::string> moveHistory; // Stores the move history

	// White team pieces
	Knight _whiteKnights[2];
	King _whiteKing;
	Queen _whiteQueen;
	Bishop _whiteBishops[2];
	Pawn _whitePawns[8];
	Rook _whiteRooks[2];

	// Black team pieces
	Knight _blackKnights[2];
	King _blackKing;
	Queen _blackQueen;
	Bishop _blackBishops[2];
	Pawn _blackPawns[8];
	Rook _blackRooks[2];

};

#endif // BOARD_H
