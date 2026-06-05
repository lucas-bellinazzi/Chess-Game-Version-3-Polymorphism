#include <iostream>
#include <string>
using namespace std;
#include "tabuleiro.h"
#include "cavalo.h"

bool Cavalo::verifica_jogada( int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro)
{
   if( (abs(pos_final_i-get_linha_atual())==2 && abs(pos_final_j- get_coluna_atual())==1) || (abs(pos_final_i-get_linha_atual())==1 && abs(pos_final_j-get_coluna_atual())==2) )
   {
      tabuleiro->setMatriz(pos_final_i, pos_final_j, tabuleiro->getMatriz(get_linha_atual(), get_coluna_atual()));
		tabuleiro->setMatriz(get_linha_atual(), get_coluna_atual(), nullptr);
		inicializa_posicao(pos_final_i, pos_final_j);
      return true;
   }
   return false;
}
