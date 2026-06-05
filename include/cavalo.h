#ifndef CAVALO_H
#define CAVALO_H

#include <iostream>
#include <string>
#include <cmath>
#include "peca.h"

class Tabuleiro;

class Cavalo:public Peca
{
public:
	/*	VERIFICA_JOGADA
	 *		Recebe como parametros dois inteiros que representam uma posicao i e j (respectivamente) no tabuleiro e, um ponteiro pro tabuleiro.
	 *		Retorna um valor logico (true ou false) informando se a jogada solicitada eh valida.
	 */
	bool verifica_jogada( int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro);

	std::string retornaString() override { 

		if(getCor() == 'P') return "\u265E";
		else return "\u2658"; 
	}
};

#endif
