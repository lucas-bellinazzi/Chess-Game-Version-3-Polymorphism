#include "tabuleiro.h"
#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

//incializando pecas no tabuleiro
Tabuleiro::Tabuleiro()
{
	for(int i = 0; i < 8; i++) {

		for(int j = 0; j < 8; j++) {

			_matriz[i][j] = nullptr;
		}
	}
	//colocando pecas brancas em suas posicoes
	_cavalos_brancos[0].inicializa_posicao(7,1);
	_cavalos_brancos[0].setCor('B');
	_cavalos_brancos[1].inicializa_posicao(7,6);
	_cavalos_brancos[1].setCor('B');
	_rei_branco.inicializa_posicao(7,4);
	_rei_branco.setCor('B');
	_rainha_branca.inicializa_posicao(7,3);
	_rainha_branca.setCor('B');
	_bispos_brancos[0].inicializa_posicao(7,2);
	_bispos_brancos[0].setCor('B');
	_bispos_brancos[1].inicializa_posicao(7,5);
	_bispos_brancos[1].setCor('B');
	_torres_brancas[0].inicializa_posicao(7,0);
	_torres_brancas[0].setCor('B');
	_torres_brancas[1].inicializa_posicao(7,7);
	_torres_brancas[1].setCor('B');
	for(int i=0; i<8; i++)
	{
		_peoes_brancos[i].inicializa_posicao(6,i);
		_peoes_brancos[i].setCor('B');
	}

	//colocando pecas pretas em suas posicoes
	_cavalos_pretos[0].inicializa_posicao(0,1);
	_cavalos_pretos[0].setCor('P');
	_cavalos_pretos[1].inicializa_posicao(0,6);
	_cavalos_pretos[1].setCor('P');
	_rei_preto.inicializa_posicao(0,4);
	_rei_preto.setCor('P');
	_rainha_preta.inicializa_posicao(0,3);
	_rainha_preta.setCor('P');
	_bispos_pretos[0].inicializa_posicao(0,2);
	_bispos_pretos[0].setCor('P');
	_bispos_pretos[1].inicializa_posicao(0,5);
	_bispos_pretos[1].setCor('P');
	_torres_pretas[0].inicializa_posicao(0,0);
	_torres_pretas[0].setCor('P');
	_torres_pretas[1].inicializa_posicao(0,7);
	_torres_pretas[1].setCor('P');
	for(int i=0; i<8; i++)
	{
		_peoes_pretos[i].inicializa_posicao(1,i);
		_peoes_pretos[i].setCor('P');
	}
	//colocando pecas no tabuleiro
	_matriz[0][0] = &_torres_pretas[0];
	_matriz[0][7] = &_torres_pretas[1]; // T = torre e B = branca
	_matriz[0][1] = &_cavalos_pretos[0];
	_matriz[0][6] = &_cavalos_pretos[1];
	_matriz[0][2] = &_bispos_pretos[0];
	_matriz[0][5] = &_bispos_pretos[1];;
	_matriz[0][3] = &_rei_preto;
	_matriz[0][4] = &_rainha_preta;
	for(int i=0; i<8; i++)
	{
		_matriz[1][i] = &_peoes_pretos[i];
	}

	_matriz[7][0] = &_torres_brancas[0];
	_matriz[7][7] = &_torres_brancas[1]; // T = torre e B = branca
	_matriz[7][1] = &_cavalos_brancos[0];
	_matriz[7][6] = &_cavalos_brancos[1];
	_matriz[7][2] = &_bispos_brancos[0];
	_matriz[7][5] = &_bispos_brancos[1];
	_matriz[7][3] = &_rei_branco;
	_matriz[7][4] = &_rainha_branca;
	for(int i=0; i<8; i++)
	{
		_matriz[6][i] = &_peoes_brancos[i];
	}
}


bool Tabuleiro::jogada(const std::string& nome_peca, int pos_i_final, int pos_j_final, std::string jogada)
{
	if(pos_i_final > 7 || pos_j_final > 7 || pos_i_final < 0 || pos_j_final < 0) return false;
	//if (roque(pos_i_final, pos_j_final,nome_peca[0])== true) return true;
	//xeque_RP(0 , 4);
	//if(nome_peca == "0") return false;

	if( historico_jogadas.size() != 0 )
	{
		if( en_passant(nome_peca, pos_i_final, pos_j_final) == true )
		{
			std::cout << "Jogada por en-passant" << std::endl; 
			return true;
		} 
	}

	historico_jogadas.push_back(jogada); //armazenando a jogada realizada

	char tipo = nome_peca[0];
	char cor = nome_peca[nome_peca.size() - 1];
	int numero = nome_peca[1] - '1';

    Peca *peca = nullptr;

	if( cor == 'P')
	{
		switch(tipo)
		{

			case 'T':
				peca = &_torres_pretas[numero];
                break;
			case 'C':
                peca = &_cavalos_pretos[numero];
                break;
			case 'B':
                peca = &_bispos_pretos[numero];
                break;			
			case 'P':
				peca = &_peoes_pretos[numero];
                break;
			case 'R':
				peca = &_rei_preto;
                break;
			case 'D':
				peca = &_rainha_preta;
                break;
             default: break;
		}
	}

	else if( cor == 'B')
	{
		switch(tipo)
		{

			case 'T':
                peca = &_torres_brancas[numero];
				break;
			case 'C':
				peca = &_cavalos_brancos[numero];
                break;
			case 'B':
				peca = &_bispos_brancos[numero];
                break;
			case 'P':
				peca = &_peoes_brancos[numero];
                break;
			case 'R':
				peca = &_rei_branco;
                break;
			case 'D':
				peca = &_rainha_branca;
                break;
            default : break;
		}
	}

    peca->verifica_jogada(pos_i_final, pos_j_final, this);

	return false;
}

// ROQUE MAIOR E ROQUE MENOR
bool Tabuleiro :: roque(int pos_final_i, int pos_final_j, char ){
	if(_rei_branco.getNJogadas() == 0 && pos_final_i == 7 && pos_final_j == 6 && getMatriz(7, 5) == nullptr && getMatriz(7, 6) == nullptr && _rei_branco.getNJogadas() == 0 ){//roque menor pecas branca
		if((xeque_RB( 7, 4))==true|| (xeque_RB( 7, 6))== true)return false;
		if((xeque_RP(0,4))==true|| (xeque_RP(0,6))== true)return false;
		//std::cout<< "ROQUE MENOR BRANCAS";
		setMatriz(pos_final_i, pos_final_j, getMatriz(_rei_branco.get_linha_atual(), _rei_branco.get_coluna_atual()));
		setMatriz(_rei_branco.get_linha_atual(), _rei_branco.get_coluna_atual(), nullptr);
		_rei_branco.inicializa_posicao(pos_final_i, pos_final_j);
		_rei_branco.getNJogadas() ;
		//movimento torre
		setMatriz(7, 5, getMatriz(7, 7));
		setMatriz(7, 7, nullptr);
		_torres_brancas[1].inicializa_posicao(7, 5);
		_torres_brancas[1].setNjogadas();
		return true;
	}

	if(_rei_branco.getNJogadas() == 0 && pos_final_i == 7 && pos_final_j == 2 && getMatriz(7, 1) == nullptr && getMatriz(7,2) == nullptr && getMatriz(7, 3) == nullptr && _torres_brancas[1].getNJogadas() == 0) {//roque maior branco
		if((xeque_RB( 7, 4))==true|| (xeque_RB( 7, 2))== true)return false;
		setMatriz(pos_final_i, pos_final_j,getMatriz(_rei_branco.get_linha_atual(), _rei_branco.get_coluna_atual()));
		setMatriz(_rei_branco.get_linha_atual(), _rei_branco.get_coluna_atual(), nullptr);
		_rei_branco.inicializa_posicao(7, 2);
		_rei_branco.getNJogadas() ;
		//movimento torre
		setMatriz(7, 3,getMatriz(7, 0));
		setMatriz(7, 0, nullptr);
		_torres_brancas[0].inicializa_posicao(7, 3);
		_torres_brancas[0].setNjogadas();
		return true;
	}


	if(_rei_preto.getNJogadas() == 0 && pos_final_i == 0 && pos_final_j == 6 && getMatriz(0, 5) == nullptr && getMatriz(0, 6) == nullptr && _torres_pretas[0].getNJogadas() == 0) {//roque menor pecas branca
		//std::cout<< "ROQUE MENOR pretas";
		if((xeque_RP(0,4))==true|| (xeque_RP(0,6))== true)return false;
		setMatriz(pos_final_i, pos_final_j, getMatriz(_rei_preto.get_linha_atual(), _rei_preto.get_coluna_atual()));
		setMatriz(_rei_preto.get_linha_atual(), _rei_preto.get_coluna_atual(), nullptr);
		_rei_preto.inicializa_posicao(pos_final_i, pos_final_j);
		_rei_preto.setNjogadas();
		//TORRE
		setMatriz(0, 5, getMatriz(0, 7));
		setMatriz(0, 7, nullptr);
		_torres_pretas[1].inicializa_posicao(0, 5);
		_torres_pretas[1].setNjogadas();
		return true;
	}


	if(_rei_preto.getNJogadas() == 0 && pos_final_i == 0 && pos_final_j == 2 && getMatriz(0, 1) == nullptr && getMatriz(0,2) == nullptr && getMatriz(0, 3) == nullptr && _torres_pretas[1].getNJogadas() == 0) {//roque maior pecas bramcas
		//std::cout<< "ROQUE MaiOR PRETAS";
		if((xeque_RP(0,4))==true|| (xeque_RP(0,2))== true)return false;
		setMatriz(pos_final_i, pos_final_j, getMatriz(_rei_preto.get_linha_atual(), _rei_preto.get_coluna_atual()));
		setMatriz(_rei_preto.get_linha_atual(), _rei_preto.get_coluna_atual(), nullptr);
		_rei_preto.inicializa_posicao(pos_final_i, pos_final_j);
		_torres_pretas[1].getNJogadas() ;
		setMatriz(0, 3, getMatriz(0, 0));
		setMatriz(0, 0, nullptr);
		_torres_pretas[0].inicializa_posicao(0, 3);
		_torres_pretas[0].setNjogadas();
		return true;

	}
	return false;


}

//XEQUE PRETO
bool Tabuleiro:: xeque_RP( int n , int m){//da pra verificar na (0,2)(0,4)(0,6) os risco para o rei
	/*int i = n;
	int j = m;

	if (m == 0 && n == 6){
		for (int j = 0; j < 8; j++){
			if ((getMatriz(1, j) == &_cavalos_pretos[0]) || (getMatriz(1, j) == &_cavalos_pretos[0])){
				if( (j == 2)|| (j == 4) ||(j == 6)){
					return true;
				}
			}
			if ((getMatriz(2, j) == &_cavalos_pretos[0]) || (getMatriz(2, j) == &_cavalos_pretos[1])){
				if( (j == 3)|| (j == 5) ||(j == 7)){
					return true;
				}
			}
		}
	}
	if (m == 0 && n == 2){
		for (int j = 0; j < 8; j++){
			if ((getMatriz(1, j) == "C1P") || (getMatriz(1, j) == "C2P")){
				if( (j == 4)|| (j == 2) ||(j == 0)||(j == 6)){
					return true;
				}
			}
			if ((getMatriz(2, j) == "C1P") || (getMatriz(2, j) == "C2P")){
				if( (j == 5)|| (j == 3) ||(j == 1)){
					return true;
				}
			}
		}
	}
	while( j > 0 ){
	//percorrendo para direita reto e analisando se tem alguna peca a adversaria""
				std::cout<<"DANIELA";
		if(getMatriz(i, j) != nullptr){
			if(((i == 1 ) && (j == 3)) || ((i == 1) && (j == 1)) || ((i == 1) && (j == 5))){

				if((getMatriz(i, j) == "P1B") ||(getMatriz(i, j) == "P2B")||(getMatriz(i, j) == "P3B") ||
				 (getMatriz(i, j) == "P4B" )||(getMatriz(i, j) == "P5B") ||(getMatriz(i, j) == "P6B" ) ||
				 (getMatriz(i, j) == "P7B" )|| (getMatriz(i, j) == "P8B")){
					return true;
				}
			}
			if(getMatriz(i, j) == "B1B" || getMatriz(i, j) == "B2B"|| getMatriz(i,j) == "RB" ){//a primeira peca no caminho for uma dessa ta em xeque
					return true;
			}
			else{j = 0;}
		}
		i++;
		j--;
	}
	i = n;
	i = m;

	while( j < 7){
		if(getMatriz(i, j) != nullptr){
			if((i == 1 && j == 3) ||(i == 1 && j == 5) || (i == 1 && j ==7)){
				if((getMatriz(i, j) == "P1B") ||(getMatriz(i, j) == "P2B")||(getMatriz(i, j) == "P3B") ||
				 (getMatriz(i, j) == "P4B" )||(getMatriz(i, j) == "P5B") ||(getMatriz(i, j) == "P6B" ) ||
				 (getMatriz(i, j) == "P7B" )|| (getMatriz(i, j) == "P8B")){return true;}
			}
			if(getMatriz(i, j) == "B1B" || getMatriz(i, j) == "B2B"|| getMatriz(i,j) == "RB" ){//a primeira peca no caminho for uma dessa ta em xeque
					return true;
			}
			else{j = 3;}
			}
		i++;
		j++;
	}
	i = n;
	i = m;

	while(  j < 7){

		if(getMatriz(i, j) != nullptr){
			if(getMatriz(i, j) == "T1B" || getMatriz(i, j) == "T2B"|| getMatriz(i,j) == "RB" ){//a primeira peca no caminho for uma dessa ta em xeque
					return true;
			}
			else{j = 3;}
		}
		i++;

	}*/
	return false;
}

//XEQUE BRANCO
bool Tabuleiro:: xeque_RB( int n , int m){//da pra verificar na (0,2)(0,4)(0,6) os risco para o rei
	/*
	if (m == 7 && n ==6){
		for (int j = 0; j < 8; j++){
			if ((getMatriz(1, j) == "C1P") || (getMatriz(1, j) == "C2P")){
				if( (j == 2)|| (j == 4) ||(j == 6)){
					return true;
				}
			}
			if ((getMatriz(2, j) == "C1P") || (getMatriz(2, j) == "C2P")){
				if( (j == 3)|| (j == 5) ||(j == 7)){
					return true;
				}
			}
		}
	}
	if (m == 7 && n == 2){
		for (int j = 0; j < 8; j++){
			if ((getMatriz(1, j) == "C1P") || (getMatriz(1, j) == "C2P")){
				if( (j == 4)|| (j == 2) ||(j == 0)||(j == 6)){
					return true;
				}
			}
			if ((getMatriz(2, j) == "C1P") || (getMatriz(2, j) == "C2P")){
				if( (j == 5)|| (j == 3) ||(j == 1)){
					return true;
				}
			}
		}
	}
	int i = n;
	int j = m;
	while( j > 0 ){
	//percorrendo para direita reto e analisando se tem alguna peca a adversaria""

		if(getMatriz(i, j) != nullptr){
			if(((i == 6 ) && (j == 1)) || ((i == 6) && (j == 3)) || ((i == 6) && (j == 5))){

				if((getMatriz(i, j) == "P1P") ||(getMatriz(i, j) == "P2P")||(getMatriz(i, j) == "P3P") ||
				 (getMatriz(i, j) == "P4P" )||(getMatriz(i, j) == "P5P") ||(getMatriz(i, j) == "P6P" ) ||
				 (getMatriz(i, j) == "P7P" )|| (getMatriz(i, j) == "P8P")){
					return true;
				}
			}
			if(getMatriz(i, j) == "B1P" || getMatriz(i, j) == "B2P"|| getMatriz(i,j) == "RP" ){//a primeira peca no caminho for uma dessa ta em xeque
					return true;
			}
			else{j = 0;}
		}
		i++;
		j--;
	}
	i = n;
	i = m;

	while( j < 7){
		if(getMatriz(i, j) != nullptr){
			if((i == 6 && j == 3) ||(i == 6 && j == 5) || (i == 6 && j ==7)){
				if((getMatriz(i, j) == "P1P") ||(getMatriz(i, j) == "P2P")||(getMatriz(i, j) == "P3P") ||
				 (getMatriz(i, j) == "P4P" )||(getMatriz(i, j) == "P5P") ||(getMatriz(i, j) == "P6P" ) ||
				 (getMatriz(i, j) == "P7P" )|| (getMatriz(i, j) == "P8P")){return true;}
			}
			if(getMatriz(i, j) == "B1P" || getMatriz(i, j) == "B2P"|| getMatriz(i,j) == "RP" ){//a primeira peca no caminho for uma dessa ta em xeque
					return true;
			}
			else{j = 3;}
			}
		i--;
		j++;
	}
	i = n;
	i = m;

	while(  i > 0){
		if(getMatriz(i, j) != nullptr){
			if(getMatriz(i, j) == "T1P" || getMatriz(i, j) == "T2P"|| getMatriz(i,j) == "RP" ){//a primeira peca no caminho for uma dessa ta em xeque
					return true;
			}
			else{j = 3;}
		}
		i--;

	}*/
	return false;
}
