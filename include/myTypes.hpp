//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
//
//   Provides useful abbreviations for the most commonly used types
//   The naming convention is very clear!
//
// FOR EMACS:
//   Do not forget to modify the file emacs-lisp/font-lock.el to
// include new types. (To find the place, search for MTci)
//   To verify if it is working, simply close and reopen emacs with this
// file. If the new types have the same color as the old ones, it means
// it is working.
//________________________________________________________
//A.Z. - 07/05 => Creation
//       12/05 => Comment about emacs.
//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
#ifndef MYTYPES_HPP
#define MYTYPES_HPP

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

#endif /* MYTYPES_HPP */
