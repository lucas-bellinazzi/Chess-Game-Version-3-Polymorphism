#ifndef REI_H
#define REI_H

#include <iostream>
#include <string>
#include "peca.h"

class Tabuleiro;

class Rei:public Peca
{
public:
	bool verifica_jogada( int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro);	

	std::string retornaString() override { 

		if(getCor() == 'P') return "\u265B";
		else return "\u2655"; 
	}
};

#endif
