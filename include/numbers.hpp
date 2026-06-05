//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
// Library containing various functions for number manipulations.
//________________________________________________________
//A.Z. - 03/05 => Creation
//       11/05 => Removed the itos function
//       01/06 => Using stringstream made the decompose function more than
//                2 times faster. Overloaded the name to ntos.
//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
#ifndef NUMBERS_H
#define NUMBERS_H


#include <deque>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iostream>
using namespace std;


template < class N > inline string ntos(const N &);
template < class N > inline string ntos(const N &, const N &);
void binary(int,int,deque<int> &);




//==============================================================================
// Converts any number to string
template < class N >
inline string ntos(const N &n){
  ostringstream s;
  s << n;
  return s.str();
}




//==============================================================================
// Given a number n, decomposes it into the number of digits of model N:
// Example ( N=5000 -> 4 digits )
// 1    --> 0001
// 25   --> 0025
// 125  --> 0125
// 3125 --> 3125
template < class N >
inline string ntos(const N&model, const N &n){

  // Number of digits of the model number
  stringstream smodel;
  smodel << model;
  const int length = int(smodel.str().length());

  // Formats output
  stringstream sn;
  sn.width(length);
  sn.fill('0');

  // Generates number
  sn << n;
  return sn.str();
}




//==============================================================================
// Given a number n, decomposes it into a binary number, and places it in N digits
// Example: N = 5
// n=0 --> 0 0 0 0 0
// n=1 --> 0 0 0 0 1
// n=2 --> 0 0 0 1 0
void binary(int n, int N, deque<int> &bin){
  bin.clear(); 

  while( n>0 ){        // Gets the number in binary format
    int mod = n%2;
    n -= mod;
    n /= 2;
    bin.push_front(mod);
  }

  int size=int(bin.size()); // Fills the rest
  for( int i=size; i<N; i++ ){
    bin.push_front(0);
  }

  if(size>N){          // If it doesn't fit in the space
    cerr << "\n\aIt is not possible to write the number in binary format containing"
	 << " only " << N << " digits! ABORTING ..." << endl;
    exit(1);
  }
}



#endif /* NUMBERS_H */
