#include "board.h"
#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Initializing pieces on the board
Board::Board()
{
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			_matrix[i][j] = nullptr;
		}
	}

	// Placing white pieces in their positions
	_whiteKnights[0].initializePosition(7, 1);
	_whiteKnights[0].setColor('W');
	_whiteKnights[1].initializePosition(7, 6);
	_whiteKnights[1].setColor('W');
	_whiteKing.initializePosition(7, 4);
	_whiteKing.setColor('W');
	_whiteQueen.initializePosition(7, 3);
	_whiteQueen.setColor('W');
	_whiteBishops[0].initializePosition(7, 2);
	_whiteBishops[0].setColor('W');
	_whiteBishops[1].initializePosition(7, 5);
	_whiteBishops[1].setColor('W');
	_whiteRooks[0].initializePosition(7, 0);
	_whiteRooks[0].setColor('W');
	_whiteRooks[1].initializePosition(7, 7);
	_whiteRooks[1].setColor('W');
	for(int i = 0; i < 8; i++)
	{
		_whitePawns[i].initializePosition(6, i);
		_whitePawns[i].setColor('W');
	}

	// Placing black pieces in their positions
	_blackKnights[0].initializePosition(0, 1);
	_blackKnights[0].setColor('B');
	_blackKnights[1].initializePosition(0, 6);
	_blackKnights[1].setColor('B');
	_blackKing.initializePosition(0, 4);
	_blackKing.setColor('B');
	_blackQueen.initializePosition(0, 3);
	_blackQueen.setColor('B');
	_blackBishops[0].initializePosition(0, 2);
	_blackBishops[0].setColor('B');
	_blackBishops[1].initializePosition(0, 5);
	_blackBishops[1].setColor('B');
	_blackRooks[0].initializePosition(0, 0);
	_blackRooks[0].setColor('B');
	_blackRooks[1].initializePosition(0, 7);
	_blackRooks[1].setColor('B');
	for(int i = 0; i < 8; i++)
	{
		_blackPawns[i].initializePosition(1, i);
		_blackPawns[i].setColor('B');
	}

	// Putting pieces on the board matrix
	_matrix[0][0] = &_blackRooks[0];
	_matrix[0][7] = &_blackRooks[1];
	_matrix[0][1] = &_blackKnights[0];
	_matrix[0][6] = &_blackKnights[1];
	_matrix[0][2] = &_blackBishops[0];
	_matrix[0][5] = &_blackBishops[1];
	_matrix[0][3] = &_blackKing;
	_matrix[0][4] = &_blackQueen;
	for(int i = 0; i < 8; i++)
	{
		_matrix[1][i] = &_blackPawns[i];
	}

	_matrix[7][0] = &_whiteRooks[0];
	_matrix[7][7] = &_whiteRooks[1];
	_matrix[7][1] = &_whiteKnights[0];
	_matrix[7][6] = &_whiteKnights[1];
	_matrix[7][2] = &_whiteBishops[0];
	_matrix[7][5] = &_whiteBishops[1];
	_matrix[7][3] = &_whiteKing;
	_matrix[7][4] = &_whiteQueen;
	for(int i = 0; i < 8; i++)
	{
		_matrix[6][i] = &_whitePawns[i];
	}
}


bool Board::move(const std::string& piece_name, int final_row, int final_col, std::string move_str)
{
	if(final_row > 7 || final_col > 7 || final_row < 0 || final_col < 0) return false;

	if(moveHistory.size() != 0)
	{
		if(en_passant(piece_name, final_row, final_col) == true)
		{
			std::cout << "Move by en-passant" << std::endl; 
			return true;
		} 
	}

	moveHistory.push_back(move_str); // Storing the performed move

	char type = piece_name[0];
	char color = piece_name[piece_name.size() - 1];
	int number = piece_name[1] - '1';

	Piece *piece = nullptr;

	if(color == 'B')
	{
		switch(type)
		{
			case 'R': // Rook
				piece = &_blackRooks[number];
				break;
			case 'N': // Knight
				piece = &_blackKnights[number];
				break;
			case 'B': // Bishop
				piece = &_blackBishops[number];
				break;			
			case 'P': // Pawn
				piece = &_blackPawns[number];
				break;
			case 'K': // King
				piece = &_blackKing;
				break;
			case 'Q': // Queen
				piece = &_blackQueen;
				break;
			default: break;
		}
	}
	else if(color == 'W')
	{
		switch(type)
		{
			case 'R': // Rook
				piece = &_whiteRooks[number];
				break;
			case 'N': // Knight
				piece = &_whiteKnights[number];
				break;
			case 'B': // Bishop
				piece = &_whiteBishops[number];
				break;
			case 'P': // Pawn
				piece = &_whitePawns[number];
				break;
			case 'K': // King
				piece = &_whiteKing;
				break;
			case 'Q': // Queen
				piece = &_whiteQueen;
				break;
			default : break;
		}
	}

	if(piece != nullptr)
	{
		piece->validateMove(final_row, final_col, this);
	}

	return false;
}

// KING-SIDE AND QUEEN-SIDE CASTLING
bool Board::castle(int final_row, int final_col, char)
{
	if(_whiteKing.getMovesCount() == 0 && final_row == 7 && final_col == 6 && getPieceAt(7, 5) == nullptr && getPieceAt(7, 6) == nullptr && _whiteKing.getMovesCount() == 0) // short castle white pieces
	{
		if(isWhiteKingInCheck(7, 4) == true || isWhiteKingInCheck(7, 6) == true) return false;
		if(isBlackKingInCheck(0, 4) == true || isBlackKingInCheck(0, 6) == true) return false;
		setPieceAt(final_row, final_col, getPieceAt(_whiteKing.getCurrentRow(), _whiteKing.getCurrentColumn()));
		setPieceAt(_whiteKing.getCurrentRow(), _whiteKing.getCurrentColumn(), nullptr);
		_whiteKing.initializePosition(final_row, final_col);
		_whiteKing.getMovesCount();
		
		// Rook movement
		setPieceAt(7, 5, getPieceAt(7, 7));
		setPieceAt(7, 7, nullptr);
		_whiteRooks[1].initializePosition(7, 5);
		_whiteRooks[1].setMovesCount();
		return true;
	}

	if(_whiteKing.getMovesCount() == 0 && final_row == 7 && final_col == 2 && getPieceAt(7, 1) == nullptr && getPieceAt(7, 2) == nullptr && getPieceAt(7, 3) == nullptr && _whiteRooks[1].getMovesCount() == 0) // long castle white pieces
	{
		if(isWhiteKingInCheck(7, 4) == true || isWhiteKingInCheck(7, 2) == true) return false;
		setPieceAt(final_row, final_col, getPieceAt(_whiteKing.getCurrentRow(), _whiteKing.getCurrentColumn()));
		setPieceAt(_whiteKing.getCurrentRow(), _whiteKing.getCurrentColumn(), nullptr);
		_whiteKing.initializePosition(7, 2);
		_whiteKing.getMovesCount();
		
		// Rook movement
		setPieceAt(7, 3, getPieceAt(7, 0));
		setPieceAt(7, 0, nullptr);
		_whiteRooks[0].initializePosition(7, 3);
		_whiteRooks[0].setMovesCount();
		return true;
	}

	if(_blackKing.getMovesCount() == 0 && final_row == 0 && final_col == 6 && getPieceAt(0, 5) == nullptr && getPieceAt(0, 6) == nullptr && _blackRooks[0].getMovesCount() == 0) // short castle black pieces
	{
		if(isBlackKingInCheck(0, 4) == true || isBlackKingInCheck(0, 6) == true) return false;
		setPieceAt(final_row, final_col, getPieceAt(_blackKing.getCurrentRow(), _blackKing.getCurrentColumn()));
		setPieceAt(_blackKing.getCurrentRow(), _blackKing.getCurrentColumn(), nullptr);
		_blackKing.initializePosition(final_row, final_col);
		_blackKing.setMovesCount();
		
		// Rook movement
		setPieceAt(0, 5, getPieceAt(0, 7));
		setPieceAt(0, 7, nullptr);
		_blackRooks[1].initializePosition(0, 5);
		_blackRooks[1].setMovesCount();
		return true;
	}

	if(_blackKing.getMovesCount() == 0 && final_row == 0 && final_col == 2 && getPieceAt(0, 1) == nullptr && getPieceAt(0, 2) == nullptr && getPieceAt(0, 3) == nullptr && _blackRooks[1].getMovesCount() == 0) // long castle black pieces
	{
		if(isBlackKingInCheck(0, 4) == true || isBlackKingInCheck(0, 2) == true) return false;
		setPieceAt(final_row, final_col, getPieceAt(_blackKing.getCurrentRow(), _blackKing.getCurrentColumn()));
		setPieceAt(_blackKing.getCurrentRow(), _blackKing.getCurrentColumn(), nullptr);
		_blackKing.initializePosition(final_row, final_col);
		_blackRooks[1].getMovesCount();
		
		// Rook movement
		setPieceAt(0, 3, getPieceAt(0, 0));
		setPieceAt(0, 0, nullptr);
		_blackRooks[0].initializePosition(0, 3);
		_blackRooks[0].setMovesCount();
		return true;
	}
	return false;
}

// BLACK CHECK DETECTION
bool Board::isBlackKingInCheck(int n, int m)
{
	/*int i = n;
	int j = m;

	if (m == 0 && n == 6){
		for (int j = 0; j < 8; j++){
			if ((getPieceAt(1, j) == &_blackKnights[0]) || (getPieceAt(1, j) == &_blackKnights[0])){
				if( (j == 2)|| (j == 4) ||(j == 6)){
					return true;
				}
			}
			if ((getPieceAt(2, j) == &_blackKnights[0]) || (getPieceAt(2, j) == &_blackKnights[1])){
				if( (j == 3)|| (j == 5) ||(j == 7)){
					return true;
				}
			}
		}
	}
	if (m == 0 && n == 2){
		for (int j = 0; j < 8; j++){
			if ((getPieceAt(1, j) == "N1B") || (getPieceAt(1, j) == "N2B")){
				if( (j == 4)|| (j == 2) ||(j == 0)||(j == 6)){
					return true;
				}
			}
			if ((getPieceAt(2, j) == "N1B") || (getPieceAt(2, j) == "N2B")){
				if( (j == 5)|| (j == 3) ||(j == 1)){
					return true;
				}
			}
		}
	}
	while( j > 0 ){
		if(getPieceAt(i, j) != nullptr){
			if(((i == 1 ) && (j == 3)) || ((i == 1) && (j == 1)) || ((i == 1) && (j == 5))){
				if((getPieceAt(i, j) == "P1W") ||(getPieceAt(i, j) == "P2W")||(getPieceAt(i, j) == "P3W") ||
				 (getPieceAt(i, j) == "P4W" )||(getPieceAt(i, j) == "P5W") ||(getPieceAt(i, j) == "P6W" ) ||
				 (getPieceAt(i, j) == "P7W" )|| (getPieceAt(i, j) == "P8W")){
					return true;
				}
			}
			if(getPieceAt(i, j) == "B1W" || getPieceAt(i, j) == "B2W"|| getPieceAt(i,j) == "KW" ){
					return true;
			}
			else{j = 0;}
		}
		i++;
		j--;
	}
	i = n;
	i = m;

	while( j < 7){
		if(getPieceAt(i, j) != nullptr){
			if((i == 1 && j == 3) ||(i == 1 && j == 5) || (i == 1 && j ==7)){
				if((getPieceAt(i, j) == "P1W") ||(getPieceAt(i, j) == "P2W")||(getPieceAt(i, j) == "P3W") ||
				 (getPieceAt(i, j) == "P4W" )||(getPieceAt(i, j) == "P5W") ||(getPieceAt(i, j) == "P6W" ) ||
				 (getPieceAt(i, j) == "P7W" )|| (getPieceAt(i, j) == "P8W")){return true;}
			}
			if(getPieceAt(i, j) == "B1W" || getPieceAt(i, j) == "B2W"|| getPieceAt(i,j) == "KW" ){
					return true;
			}
			else{j = 3;}
			}
		i++;
		j++;
	}
	i = n;
	i = m;

	while(  j < 7){
		if(getPieceAt(i, j) != nullptr){
			if(getPieceAt(i, j) == "R1W" || getPieceAt(i, j) == "R2W"|| getPieceAt(i,j) == "KW" ){
					return true;
			}
			else{j = 3;}
		}
		i++;
	}*/
	return false;
}

// WHITE CHECK DETECTION
bool Board::isWhiteKingInCheck(int n, int m)
{
	/*
	if (m == 7 && n ==6){
		for (int j = 0; j < 8; j++){
			if ((getPieceAt(1, j) == "N1B") || (getPieceAt(1, j) == "N2B")){
				if( (j == 2)|| (j == 4) ||(j == 6)){
					return true;
				}
			}
			if ((getPieceAt(2, j) == "N1B") || (getPieceAt(2, j) == "N2B")){
				if( (j == 3)|| (j == 5) ||(j == 7)){
					return true;
				}
			}
		}
	}
	if (m == 7 && n == 2){
		for (int j = 0; j < 8; j++){
			if ((getPieceAt(1, j) == "N1B") || (getPieceAt(1, j) == "N2B")){
				if( (j == 4)|| (j == 2) ||(j == 0)||(j == 6)){
					return true;
				}
			}
			if ((getPieceAt(2, j) == "N1B") || (getPieceAt(2, j) == "N2B")){
				if( (j == 5)|| (j == 3) ||(j == 1)){
					return true;
				}
			}
		}
	}
	int i = n;
	int j = m;
	while( j > 0 ){
		if(getPieceAt(i, j) != nullptr){
			if(((i == 6 ) && (j == 1)) || ((i == 6) && (j == 3)) || ((i == 6) && (j == 5))){
				if((getPieceAt(i, j) == "P1B") ||(getPieceAt(i, j) == "P2B")||(getPieceAt(i, j) == "P3B") ||
				 (getPieceAt(i, j) == "P4B" )||(getPieceAt(i, j) == "P5B") ||(getPieceAt(i, j) == "P6B" ) ||
				 (getPieceAt(i, j) == "P7B" )|| (getPieceAt(i, j) == "P8B")){
					return true;
				}
			}
			if(getPieceAt(i, j) == "B1B" || getPieceAt(i, j) == "B2B"|| getPieceAt(i,j) == "KB" ){
					return true;
			}
			else{j = 0;}
		}
		i++;
		j--;
	}
	i = n;
	i = m;

	while( j < 7){
		if(getPieceAt(i, j) != nullptr){
			if((i == 6 && j == 3) ||(i == 6 && j == 5) || (i == 6 && j ==7)){
				if((getPieceAt(i, j) == "P1B") ||(getPieceAt(i, j) == "P2B")||(getPieceAt(i, j) == "P3B") ||
				 (getPieceAt(i, j) == "P4B" )||(getPieceAt(i, j) == "P5B") ||(getPieceAt(i, j) == "P6B" ) ||
				 (getPieceAt(i, j) == "P7B" )|| (getPieceAt(i, j) == "P8B")){return true;}
			}
			if(getPieceAt(i, j) == "B1B" || getPieceAt(i, j) == "B2B"|| getPieceAt(i,j) == "KB" ){
					return true;
			}
			else{j = 3;}
			}
		i--;
		j++;
	}
	i = n;
	i = m;

	while(  i > 0){
		if(getPieceAt(i, j) != nullptr){
			if(getPieceAt(i, j) == "R1B" || getPieceAt(i, j) == "R2B"|| getPieceAt(i,j) == "KB" ){
					return true;
			}
			else{j = 3;}
		}
		i--;
	}*/
	return false;
}
