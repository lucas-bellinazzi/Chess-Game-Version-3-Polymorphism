#ifndef IMPRESSAO_TERMINAL
#define IMPRESSAO_TERMINAL

#include <iostream>
#include <string.h>
#include "tabuleiro.h"

void impressao(const Tabuleiro &t);
void impressao(const Tabuleiro &t)
{

	std::cout << "   a  b  c  d  e  f  g  h  " << std::endl;
	std::cout << " ---------------------------" << std::endl;
	
	for(int i = 0 ; i < 8 ; i++) {

		std::cout << i + 1 << '|';

		for(int j = 0; j < 8 ; j++) {

			Peca *peca = t.getMatriz(i, j);

			if(peca) std::cout << ' ' << peca->retornaString() << ' ';
			else std::cout << " - ";
		}

		std::cout << '|' << i + 1 << std::endl;
	}	

	std::cout << "---------------------------" << std::endl;
	std::cout << "   a  b  c  d  e  f  g  h  " << std::endl;		

}

#endif