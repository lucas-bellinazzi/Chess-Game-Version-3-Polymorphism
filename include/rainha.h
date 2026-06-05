#ifndef RAINHA_H
#define RAINHA_H

#include <iostream>
#include <string>
#include "peca.h"

class Tabuleiro;

class Rainha:public Peca
{

public:	
	bool verifica_jogada( int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro);
	
private:

	int peca_no_caminho_torre(int pos_atual_i, int pos_atual_j, int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro);
  	int peca_no_caminho_bispo(int pos_atual_i, int pos_atual_j, int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro);  

  	std::string retornaString() override { 

		if(getCor() == 'P') return "\u265A";
		else return "\u2654"; 
	}
};

#endif
