#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <string>
#include <vector>

#include "cavalo.h"
#include "rei.h"
#include "rainha.h"
#include "bispo.h"
#include "peao.h"
#include "torre.h"

class Tabuleiro {

public:

	//incializando pecas no tabuleiro
	Tabuleiro();

	bool ehReiPreto(Peca *p) { return p == &_rei_preto; }
	bool ehReiBranco(Peca *p) { return p == &_rei_branco; }

	Peca *getMatriz(int lin, int col) const {return _matriz[lin][col];}

	void setMatriz(int lin, int col, Peca *pec) {_matriz[lin][col] = pec;}

	int switch_para_letra(char letra)
	{
		switch(letra)
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

	int switch_para_numero(char numero)
	{
		switch(numero)
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

	std::string switch_char_string(char letra)
	{
		switch(letra)
		{
			case 'C':
				return std::string("C");
			case 'T':
				return std::string("T");
			case 'B':
				return std::string("B");
			case 'D':
				return std::string("D");
			case 'R':
				return std::string("R");
			default: return std::string ("erro");
		}

		return std::string("erro");
	}


	void decofica_jogada_anterior( char cor_peca_atual, std::string &nome_peca_anterior, int &linha_peca_anterior, int &coluna_peca_anterior, std::string jogada_anterior )
	{
		char cor_peca_anterior;

		if(cor_peca_atual == 'P') cor_peca_anterior = 'B';
		else cor_peca_anterior = 'P';

		linha_peca_anterior = switch_para_numero(char(jogada_anterior[1]));
		coluna_peca_anterior = switch_para_letra(char(jogada_anterior[0]));
		nome_peca_anterior = std::string("P") + char('1' + switch_para_letra(jogada_anterior[0])) + cor_peca_anterior;
		return;
	}

	bool en_passant( std::string nome_peca, int linha_final, int coluna_final )
	{			
		//nome_peca esta no padrao P1P ou P1B sendo o 1 um numero qualquer de 1 a 8
		//linha_final eh a linha final ao qual o peao ira se deslocar
		//coluna_final eh a coluna final ao qual o peao ira se deslocar		
		std::string nome_peca_anterior;
		int linha_peca_anterior, coluna_peca_anterior;

		std::string jogada_anterior = historico_jogadas[historico_jogadas.size()-1];//pega a ultima jogada
		decofica_jogada_anterior( nome_peca[2],nome_peca_anterior, linha_peca_anterior, coluna_peca_anterior, jogada_anterior );

		//pegando posicao de cada peao
		int numero = nome_peca[1] - '1';
		int numero_anterior = nome_peca_anterior[1] - '1';

		if( historico_jogadas.size() != 0 ) //evitar erro de segmentacao
		{			
			if( nome_peca_anterior[0] == 'P' && nome_peca[0] == 'P' ) //verificando se sao dois peoes
			{
				//caso branco tenha que comer o peao preto
				if( nome_peca_anterior[2] == 'P'&& _peoes_pretos[coluna_peca_anterior].get_duas_vezes() == true) //caso o peao que sera comido andou duas casas
				{
					if(_peoes_pretos[coluna_peca_anterior].get_linha_atual() == 3 && linha_final+1 == 3) //caso estejam na linha 5 do xadrez
					{
						if( abs(linha_final- _peoes_brancos[numero].get_linha_atual()) == 2 ) _peoes_brancos[numero].set_duas_vezes_true();
   	  					else _peoes_brancos[numero].set_duas_vezes_false();

						setMatriz(linha_final, coluna_final, getMatriz(_peoes_brancos[numero].get_linha_atual(), _peoes_brancos[numero].get_coluna_atual()));
            			setMatriz(_peoes_brancos[numero].get_linha_atual(), _peoes_brancos[numero].get_coluna_atual(), nullptr);
            			setMatriz(_peoes_pretos[numero_anterior].get_linha_atual(), _peoes_pretos[numero_anterior].get_coluna_atual(), nullptr);
            			_peoes_brancos[numero].inicializa_posicao(linha_final, coluna_final);
           				_peoes_brancos[numero].incremento_nJogadas();            
						return true;
					}

					else return false;
				}

				//caso preta tenha que comer o peao branco
				else if( nome_peca_anterior[2] == 'B'&& _peoes_brancos[coluna_peca_anterior].get_duas_vezes() == true) //caso o peao que sera comido andou duas casas
				{
					if(_peoes_brancos[coluna_peca_anterior].get_linha_atual() == 4 && linha_final-1 == 4) //caso estejam na linha 5 do xadrez
					{
						if( abs(linha_final- _peoes_pretos[numero].get_linha_atual()) == 2 ) _peoes_pretos[numero].set_duas_vezes_true();
   	  					else _peoes_pretos[numero].set_duas_vezes_false();

						setMatriz(linha_final, coluna_final, getMatriz(_peoes_pretos[numero].get_linha_atual(), _peoes_pretos[numero].get_coluna_atual()));
            			setMatriz(_peoes_pretos[numero].get_linha_atual(), _peoes_pretos[numero].get_coluna_atual(), nullptr);
            			setMatriz(_peoes_brancos[numero_anterior].get_linha_atual(), _peoes_brancos[numero_anterior].get_coluna_atual(), nullptr);
            			_peoes_pretos[numero].inicializa_posicao(linha_final, coluna_final);
           				_peoes_pretos[numero].incremento_nJogadas();            
						return true;
					}

					else return false;
				}

				else return false;
			}

			else return false;
		}

		else return false;
	}

	bool roque(int, int, char);

	bool xeque_RP(int n, int m);

	bool xeque_RB( int n , int m);

	bool jogada(const std::string& nome_peca, int pos_i_final, int pos_j_final, std::string jogada);

	std::vector<std::string> getHistoricoJogadas() { return historico_jogadas; }

	//adicionar funcoes conforme necessidade

private:
	//matriz = tabuleiro
	Peca *_matriz[8][8]; // "_" significa privado

	std::vector<std::string> historico_jogadas; //armazena o historico de jogadas

	//pecas do time branco
	Cavalo _cavalos_brancos[2];
	Rei _rei_branco;
	Rainha _rainha_branca;
	Bispo _bispos_brancos[2];
	Peao _peoes_brancos[8];
	Torre _torres_brancas[2];

	//pecas do time preto
	Cavalo _cavalos_pretos[2];
	Rei _rei_preto;
	Rainha _rainha_preta;
	Bispo _bispos_pretos[2];
	Peao _peoes_pretos[8];
	Torre _torres_pretas[2];

};

#endif // TABULEIRO_H
