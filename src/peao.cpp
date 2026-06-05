#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;
#include "tabuleiro.h"
#include "peao.h"

bool Peao::verifica_jogada( int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro)
{

   char cor = tabuleiro->getMatriz(get_linha_atual(), get_coluna_atual())->getCor();

   //PEAO CAPTURA
   if( tabuleiro->getMatriz(pos_final_i, pos_final_j)!=nullptr && tabuleiro->getMatriz(pos_final_i, pos_final_j)->getCor()!=cor && abs(pos_final_i-get_linha_atual())==1 && abs(pos_final_j-get_coluna_atual())==1 )
   {
   	  if( abs(pos_final_i-get_linha_atual()) == 2 ) duas_vezes = true;
   	  else duas_vezes = false;

      tabuleiro->setMatriz(pos_final_i, pos_final_j, tabuleiro->getMatriz(get_linha_atual(), get_coluna_atual()));
      tabuleiro->setMatriz(get_linha_atual(), get_coluna_atual(), nullptr);
      inicializa_posicao(pos_final_i, pos_final_j);
      incremento_nJogadas();
      return true;
   }

   //PECAS PRETAS
   if(cor=='P')
   {
      if( pos_final_i==get_linha_atual()+1 && get_coluna_atual()==pos_final_j )
      {
         if(peca_no_caminho(get_linha_atual(),get_coluna_atual(), pos_final_i, pos_final_j, tabuleiro) == 0)
         {

         	if( abs(pos_final_i-get_linha_atual()) == 2 ) duas_vezes = true;
   	  		else duas_vezes = false;

            tabuleiro->setMatriz(pos_final_i, pos_final_j, tabuleiro->getMatriz(get_linha_atual(), get_coluna_atual()));
            tabuleiro->setMatriz(get_linha_atual(), get_coluna_atual(), nullptr);
            inicializa_posicao(pos_final_i, pos_final_j);
            incremento_nJogadas();
            return true;
         }
      }

      else if( pos_final_i==get_linha_atual()+2 && get_coluna_atual()==pos_final_j && getNJogadas()==0)
      {
         if(peca_no_caminho(get_linha_atual(),get_coluna_atual(), pos_final_i, pos_final_j, tabuleiro) == 0)
         {
         	if( abs(pos_final_i-get_linha_atual()) == 2 ) duas_vezes = true;
   	  		else duas_vezes = false;

            tabuleiro->setMatriz(pos_final_i, pos_final_j, tabuleiro->getMatriz(get_linha_atual(), get_coluna_atual()));
            tabuleiro->setMatriz(get_linha_atual(), get_coluna_atual(), nullptr);
            inicializa_posicao(pos_final_i, pos_final_j);
            incremento_nJogadas();
            return true;
         }
      }
      return false;
   }
   //PECAS BRANCAS
   else if(cor == 'B')
   {
      if( pos_final_i==get_linha_atual()-1 && get_coluna_atual()==pos_final_j )
      {
         if(peca_no_caminho(get_linha_atual(),get_coluna_atual(), pos_final_i, pos_final_j, tabuleiro) == 0)
         {
         	if( abs(pos_final_i-get_linha_atual()) == 2 ) duas_vezes = true;
   	  		else duas_vezes = false;

            tabuleiro->setMatriz(pos_final_i, pos_final_j, tabuleiro->getMatriz(get_linha_atual(), get_coluna_atual()));
            tabuleiro->setMatriz(get_linha_atual(), get_coluna_atual(), nullptr);
            inicializa_posicao(pos_final_i, pos_final_j);
            incremento_nJogadas();
            return true;
         }
      }

      else if( pos_final_i==get_linha_atual()-2 && get_coluna_atual()==pos_final_j && getNJogadas()==0)
      {
         if(peca_no_caminho(get_linha_atual(),get_coluna_atual(), pos_final_i, pos_final_j, tabuleiro) == 0)
         {
         	if( abs(pos_final_i-get_linha_atual()) == 2 ) duas_vezes = true;
   	  		else duas_vezes = false;
   	  		
            tabuleiro->setMatriz(pos_final_i, pos_final_j, tabuleiro->getMatriz(get_linha_atual(), get_coluna_atual()));
            tabuleiro->setMatriz(get_linha_atual(), get_coluna_atual(), nullptr);
            inicializa_posicao(pos_final_i, pos_final_j);
            incremento_nJogadas();
            return true;
         }
      }
      return false;
   }
   return false;
}


int Peao::peca_no_caminho(int pos_atual_i, int pos_atual_j, int pos_final_i, int pos_final_j, Tabuleiro *tabuleiro)
{
   int x = pos_atual_j;
   volatile int y = pos_atual_i;

   int valor;
   if(pos_final_i > y) valor = 1;
   else valor = -1;

   if(tabuleiro->getMatriz(pos_final_i, pos_final_j)!=  nullptr && pos_atual_j==pos_final_j)
   {
      return 1;
   }

   y += valor;
   while(y != pos_final_i)
   {

      if(tabuleiro->getMatriz(y, x)!= nullptr)
         return 1;

      y += valor;
   }
   return 0;
}