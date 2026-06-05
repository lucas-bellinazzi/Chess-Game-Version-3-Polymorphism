#ifndef ABORT_HPP
#define ABORT_HPP

#include <iostream>
#include <cstdlib>
using namespace std;

#define abort_program( error ){                                 \
  cerr << "!!  FILE: " << __FILE__ << "\n"                   \
       << "!!  LINE  : " << __LINE__ << "\n"                   \
       << "!!  " << error << "\n\a!!  ABORTING ..." << endl;    \
  exit(1);                                                      \
  }

#endif /* ABORT_HPP */
