#ifndef TERMINAL_PRINT
#define TERMINAL_PRINT

#include <iostream>
#include <string.h>
#include "board.h"

void printBoard(const Board &t);
void printBoard(const Board &t)
{

	std::cout << "   a  b  c  d  e  f  g  h  " << std::endl;
	std::cout << " ---------------------------" << std::endl;
	
	for(int i = 0 ; i < 8 ; i++) {

		std::cout << i + 1 << '|';

		for(int j = 0; j < 8 ; j++) {

			Piece *peca = t.getPieceAt(i, j);

			if(peca) std::cout << ' ' << peca->toString() << ' ';
			else std::cout << " - ";
		}

		std::cout << '|' << i + 1 << std::endl;
	}	

	std::cout << "---------------------------" << std::endl;
	std::cout << "   a  b  c  d  e  f  g  h  " << std::endl;		

}

#endif
