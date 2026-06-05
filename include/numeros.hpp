//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
// Biblioteca contendo varias funcoes para manipulacoes sobre numeros.
//________________________________________________________
//A.Z. - 03/05 => Criacao
//       11/05 => Tirei a funcao itos
//       01/06 => Usando a classe stringstream fiz a funcao decompoe ser mais
//                de 2 vezes mais rapida. Sobrecarreguei o nome para ntos.
//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
#ifndef NUMEROS_H
#define NUMEROS_H


#include <deque>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
using namespace std;


template < class N > inline string ntos(const N &);
template < class N > inline string ntos(const N &, const N &);
void binario(int,int,deque<int> &);




//==============================================================================
// Converte um numero qualquer para string
template < class N >
inline string ntos(const N &n){
  ostringstream s;
  s << n;
  return s.str();
}




//==============================================================================
// Dado um numero n, decompoe ele no numero de casas do numero N:
// Exemplo ( N=5000 -> 4 casas )
// 1    --> 0001
// 25   --> 0025
// 125  --> 0125
// 3125 --> 3125
template < class N >
inline string ntos(const N&model, const N &n){

  // Numero de casas do numero modelo
  stringstream smodel;
  smodel << model;
  const int length = smodel.str().length();

  // Formata a saida
  stringstream sn;
  sn.width(length);
  sn.fill('0');

  // Gera o numero
  sn << n;
  return sn.str();
}




//==============================================================================
// Dado um numero n, decompoe ele em um numero binario, e coloca ele em N casas
// Exemplo: N = 5
// n=0 --> 0 0 0 0 0
// n=1 --> 0 0 0 0 1
// n=2 --> 0 0 0 1 0
void binario(int n, int N, deque<int> &bin){
  bin.clear(); 

  while( n>0 ){        // Pega o numero em formato binario
    int mod = n%2;
    n -= mod;
    n /= 2;
    bin.push_front(mod);
  }

  int size=bin.size(); // Preenche o resto
  for( int i=size; i<N; i++ ){
    bin.push_front(0);
  }

  if(size>N){          // Se nao couber no espaco
    cerr << "\n\aNao eh possivel escrever o numero em formato binario contendo"
	 << " soh " << N << " casas! ABORTANDO ..." << endl;
    exit(1);
  }
}



#endif /* NUMEROS_H */
