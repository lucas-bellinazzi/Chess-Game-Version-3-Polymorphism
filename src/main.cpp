#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctype.h>

#include "board.h"
#include "terminalPrint.hpp"

// Zabot libraries
#include "abort.hpp"
#include "dataFileReader.hpp"

using namespace std;

enum{playFromFile, viaTerminal};
void loadData( vector<string> &teamMoves, char *argv[] );
void decodeMain(Board &t, string teamMoves, int position);
int letterToCol(char letter);
int numberToRow(char number);
std::string pieceCharToString(char letter);


int main( int argc, char *argv[] )
{
	// Input parameters
	bool readType = viaTerminal; // manual input or from file


	Board t;

	if(readType == playFromFile)
	{
		if( argc!=2 ) abort_program( "Wrong number of input parameters!" );
		std::vector<string> teamMoves;
		loadData(teamMoves, argv);

		int size = int(teamMoves.size());

		for(int i=0; i < size; i++)
		{
			printBoard(t);
			decodeMain(t, teamMoves[std::size_t(i)],  i);
		}
		printBoard(t);
	}

	else
	{
		int count = 0;
		for(;;)
		{
			printBoard(t);
			if( count%2 == 0 ) std::cout << "White Team Move: ";
			else std::cout << "Black Team Move: ";
			std::string moveStr;
			std::cin >> moveStr;
			if(moveStr == "end") break;

			decodeMain(t, moveStr, count);
			count++;
		}
	}
	return 0;
}


void loadData( vector<string> &teamMoves, char *argv[] )
{
	DataFileReader dfr(argv[1]);
	// Reads data
	int moveNum;
	string whiteMove, blackMove;

	for(;;)
	{
		++dfr;
		dfr >> moveNum >> whiteMove >> blackMove;
		if( whiteMove == "end" || blackMove == "end" ) break;
		teamMoves.push_back(whiteMove);
		teamMoves.push_back(blackMove);
	}

	return;
}



void decodeMain(Board &t, string teamMoves, int position)
{
	char teamColor;
	if(position%2 == 0) teamColor = 'W';
	else teamColor = 'B';

	string currentMove = teamMoves;

	// if letters are lowercase it means it is just a pawn
	if(islower(currentMove[0]) != 0)
	{
		if(currentMove.size() == 2) // just movement
		{
			string piece = std::string("P") + char('1' + letterToCol(currentMove[0])) + teamColor;
			int row = numberToRow(currentMove[1]);
			int col = letterToCol(currentMove[0]);
			cout << piece << " " << row << " " << col << endl;

			if(!t.move(piece, row, col, currentMove))
			{
				std::cout << "Invalid Move" << std::endl;
			}
		}

		else if(currentMove.size() == 4) // movement followed by capture
		{
			string piece = std::string("P") + char('1' + letterToCol(currentMove[0])) + teamColor;
			int row = numberToRow(currentMove[3]);
			int col = letterToCol(currentMove[2]);
			cout << piece << " " << row << " " << col << endl;

			if(!t.move(piece, row, col, currentMove))
			{
				std::cout << "Invalid Move" << std::endl;
			}
		}
	}

	// if uppercase it will be the remaining pieces
	else if(isupper(currentMove[0]) != 0)
	{
		if(currentMove.size() == 3) // just movement
		{
			string piece = pieceCharToString(currentMove[0]) + std::string("1") + teamColor;
			if(currentMove[0] == 'K' || currentMove[0] == 'Q' ) piece = pieceCharToString(currentMove[0]) + teamColor;
			int row = numberToRow(currentMove[2]);
			int col = letterToCol(currentMove[1]);

			if(!t.move(piece, row, col, currentMove))
			{
				piece = pieceCharToString(currentMove[0]) + std::string("2") + teamColor;
				if(currentMove[0] == 'K' || currentMove[0] == 'Q' ) piece = pieceCharToString(currentMove[0]) + teamColor;
				if(!t.move(piece, row, col, currentMove))
				{
					std::cout << "Invalid Move" << std::endl;
				}
				cout << piece << " " << row << " " << col << endl;
				return;
			}
			cout << piece << " " << row << " " << col << endl;
		}

		if(currentMove.size() == 4) // movement with capture
		{
			string piece = pieceCharToString(currentMove[0]) + std::string("1") + teamColor;
			if(currentMove[0] == 'K' || currentMove[0] == 'Q' ) piece = pieceCharToString(currentMove[0]) + teamColor;
			int row = numberToRow(currentMove[3]);
			int col = letterToCol(currentMove[2]);

			if(!t.move(piece, row, col, currentMove))
			{
				piece = pieceCharToString(currentMove[0]) + std::string("2") + teamColor;
				if(currentMove[0] == 'K' || currentMove[0] == 'Q' ) piece = pieceCharToString(currentMove[0]) + teamColor;
				if(!t.move(piece, row, col, currentMove))
				{
					std::cout << "Invalid Move" << std::endl;
				}
				cout << piece << " " << row << " " << col << endl;
				return;
			}
			cout << piece << " " << row << " " << col << endl;
		}
	}

	else return;
}



int letterToCol(char letter)
{
	switch(letter)
	{
		case 'a':
			return 0;
		case 'b':
			return 1;
		case 'c':
			return 2;
		case 'd':
			return 3;
		case 'e':
			return 4;
		case 'f':
			return 5;
		case 'g':
			return 6;
		case 'h':
			return 7;
		default: return -1;
	}

	return -1;
}

int numberToRow(char number)
{
	switch(number)
	{
		case '1':
			return 7;
		case '2':
			return 6;
		case '3':
			return 5;
		case '4':
			return 4;
		case '5':
			return 3;
		case '6':
			return 2;
		case '7':
			return 1;
		case '8':
			return 0;
		default: return -1;
	}

	return -1;
}

std::string pieceCharToString(char letter)
{
	switch(letter)
	{
		case 'N':
			return std::string("N");
		case 'R':
			return std::string("R");
		case 'B':
			return std::string("B");
		case 'Q':
			return std::string("Q");
		case 'K':
			return std::string("K");
		default: return std::string ("error");
	}

	return std::string("error");
}
