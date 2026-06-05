//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
//
//   Fornece abreviacoes uteis para os tipos mais usados
//   A regra de nomenclatura eh bem clara!
//
// PARA O EMACS:
//   Nao esqueca de alterar o arquivo emacs-lisp/font-lock.el para 
// incluir novos tipos. (Para achar o lugar, busque por MTci )
//   Para verificar se esta funcionando, basta fechar e reabrir o emacs com este
// arquivo. Se os novos tipos tiverem a mesma cor dos antigos, eh porque esta
// funcionando.
//________________________________________________________
//A.Z. - 07/05 => Criacao
//       12/05 => O comentario sobre o emacs.
//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
#ifndef MEUSTIPOS_HPP
#define MEUSTIPOS_HPP

#include <vector>
#include <string>

typedef const int                             MTci;
typedef const bool                            MTcb;
typedef const long                            MTcl;
typedef const float                           MTcf;
typedef const double                          MTcd;
typedef const std::string                     MTcs;
                                              
typedef std::vector<int>                      MTvi;
typedef std::vector<bool>                     MTvb;
typedef std::vector<long>                     MTvl;
typedef std::vector<float>                    MTvf;
typedef std::vector<double>                   MTvd;
typedef std::vector<std::string>              MTvs;
                                              
typedef const std::vector<int>                MTcvi;
typedef const std::vector<bool>               MTcvb;
typedef const std::vector<long>               MTcvl;
typedef const std::vector<float>              MTcvf;
typedef const std::vector<double>             MTcvd;
typedef const std::vector<std::string>        MTcvs;
                                              
typedef std::vector<int>::iterator            MTvii;
typedef std::vector<bool>::iterator           MTvbi;
typedef std::vector<long>::iterator           MTvli;
typedef std::vector<float>::iterator          MTvfi;
typedef std::vector<double>::iterator         MTvdi;
typedef std::vector<std::string>::iterator    MTvsi;

#endif /* MEUSTIPOS_HPP */
