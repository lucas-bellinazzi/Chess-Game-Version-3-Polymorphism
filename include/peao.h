#ifndef PEAO_H
#define PEAO_H

#include <iostream>
#include <string>
#include "peca.h"

class Tabuleiro;

class Peao:public Peca
{
public:	
	bool verifica_jogada( int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro);	
	void set_duas_vezes_true() { duas_vezes = true; }
	void set_duas_vezes_false() { duas_vezes = false; }
	bool get_duas_vezes() { return duas_vezes; }

	std::string retornaString() override { 

		if(getCor() == 'P') return "\u265F";
		else return "\u2659"; 
	}
	
private:
	int peca_no_caminho(int pos_atual_i, int pos_atual_j, int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro);
	bool duas_vezes = false; //diz se andou duas casas
};

#endif
