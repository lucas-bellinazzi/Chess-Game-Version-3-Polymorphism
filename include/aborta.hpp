//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
//
// Aborts a program
//________________________________________________________
//A.Z. - 03/05 => Criacao
//       11/05 => Usa #define ao inves de uma funcao.
//                Mostra o nome do arquivo e a linha onde o erro ocorreu
//       12/15 => English
//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
#ifndef ABORTA_HPP
#define ABORTA_HPP


#include <iostream>
#include <cstdlib>
using namespace std;


#define aborta( erro ){                                         \
  cerr << "!!  FILE: " << __FILE__ << "\n"                   \
       << "!!  LINE  : " << __LINE__ << "\n"                   \
       << "!!  " << erro << "\n\a!!  ABORTING ..." << endl;    \
  exit(1);                                                      \
  }


#endif /* ABORTA_HPP */
