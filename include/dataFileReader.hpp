//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
// DataFileReader Class
//
//    This class provides an appropriate interface to read data files.
//    Ignores comments and informs the row and column number being read,
//    the number of columns of that line, among other things.
//________________________________________________________
// TODO:
//    overload the operator --
//________________________________________________________
//A.Z. - 01/06 => Creation
//       01/06 => Overloaded the operator +=
//       02/06 => Fixed the bug that caused the class to return eof if
//                no enter was given at the end of the last line of data.
//                See example program dfr2.cpp
//       10/07 => readColumn function gets the value directly at a given
//                column without incrementing as before.
//                It is more efficient than using >> multiple times until reaching
//                the column in the stream.
//       10/07 => The operator >> uses the readColumn function. Thus, gaining a lot
//                in efficiency because the previous loop is not needed.
//       10/07 => seteol function to tell the class it has read everything it wanted
//                on the line and presumably reached the end (end of line). Must
//                be used in conjunction with readColumn function.
//T.R  - 11/07 => Tiago Ribeiro: rewind function
//A.Z  - 11/07 => Small adaptations in rewind function
//       11/07 => Constructor uses rewind function
//       02/08 => Stopped reading the first line automatically. This
//                simplified the code a lot, eliminating the need
//                for an end-of-line marker -- eol !!
//       02/08 => operator++ returns boolean indicating if end of file
//                was reached or not. Direct movement in the file is very
//                simple because now it only needs a while( !++dfr ){ ... }
//       03/08 => Template method readColumn calling with template prefix because
//                of gcc 3.X
//       08/08 => More useful error message in readColumn() function
//       07/11 => set function to be able to use the object with more than one file
//       11/13 => Changed name from set to open, more obvious!
//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
#ifndef DATAFILEREADER_H
#define DATAFILEREADER_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "abort.hpp"
#include "numbers.hpp"
#include "myTypes.hpp"
using namespace std;


class DataFileReader{
  template<class T>
  friend DataFileReader &operator >> ( DataFileReader &, T & );

public:
  DataFileReader( MTcs &, MTcs & = "#" );
  ~DataFileReader(){ this->close(); }

public:
  void   commentarySymbol( MTcs &cs )       { _commentarySymbol = cs;   }
  string commentarySymbol(   void   ) const { return _commentarySymbol; }
  int    lineNumber      (   void   ) const { return _lineNumber;       }
  int    columnNumber    (   void   ) const { return _columnNumber;     }
  int    numberOfColumns (   void   ) const { return _numberOfColumns;  }

  void open( MTcs &,  MTcs & = "#");

  template<class T> T readColumn ( MTci & );

  void   close(void){  if( _FILE.is_open() ) _FILE.close(); }

  bool operator++();     // Pre-increment

  const DataFileReader &operator += ( MTci &n ){
    for( int i=0; i<n; i++ ) ++(*this);
    return (*this);   // Allows concatenation
  }

  void rewind(void);

private:
  int      _lineNumber;
  int      _columnNumber;
  int      _numberOfColumns;
  string   _commentarySymbol;
  string   _filename;
  MTvs     _lineContent;
  ifstream _FILE;
};





//------------------------------------------------------------------------------
// DESCRIPTION:
//   Constructor
DataFileReader::DataFileReader( MTcs &file, MTcs &cs ){
  this->open(file,cs);
}





//------------------------------------------------------------------------------
// DESCRIPTION:
//   Open function, to start reading a file
//   With it, I don't need to instantiate an object for each file I want to
//   read, just open(filename) and read
void DataFileReader::open( MTcs &file, MTcs &cs ){
  _commentarySymbol = cs;
  _filename=file;
  this->rewind(); // Goes to the beginning of the file and initializes the appropriate variables
}



//------------------------------------------------------------------------------
// DESCRIPTION:
//   Goes directly to column C and gets the value there.
//   If the column does not exist in the file, aborts.
// INPUT:
//   Column number
// OUTPUT:
//   Value in the column
template<class T>
T DataFileReader::readColumn( MTci &C ){
  if(C<1){
    abort_program("Columns are numbered starting from 1!");
  }
  if(C>_numberOfColumns){
    string msg="Line "+ntos(_lineNumber)+" does not have column "+ntos(C)+".";
    msg+=" In this line, columns are numbered from 1 to ";
    msg+=ntos(_numberOfColumns);
    abort_program(msg);
  }
  T v;
  stringstream ss( _lineContent[ std::size_t(C-1)] );
  ss >> v;
  return v;
}



//------------------------------------------------------------------------------
// DESCRIPTION:
//   Overload of operator >>
template<class T>
DataFileReader &operator >> ( DataFileReader &s, T &v ){

  // Gets the content of the specific column
  v = s.template readColumn<T>(s._columnNumber);

  // Increments column position. If reached end, goes back to the beginning
  s._columnNumber++;
  if( s._columnNumber == (s._numberOfColumns+1) ) s._columnNumber = 1;

  return s;
}



//------------------------------------------------------------------------------
// DESCRIPTION:
//   Pre-increment
bool DataFileReader::operator++(){

  string saux1,saux2;
  _columnNumber = 1;
  _lineContent  = MTvs();
  while(  _lineContent.empty() && !_FILE.eof() ){

    // Reads the entire line
    _lineNumber++;
    string completeLine;
    getline( _FILE, completeLine );


    // Position of comment symbol, if it exists
    unsigned int p = completeLine.find(_commentarySymbol);


    // Reads only the part that is not commented
    //if( p != string::npos )    // Has comment on line
      saux1.assign( completeLine, 0, p );
    //else                      // Does not have comment on line
      //saux1.assign( completeLine );


    // Initializes the vector _lineContent
    stringstream ssaux(saux1);
    while( ssaux >> saux2 ) _lineContent.push_back(saux2);
    _numberOfColumns = int(_lineContent.size());
  }

  // Phenomenal!
  // With this test we can read until the end of the data files, whether
  // EOF is on the data line or on a new line.
  return (_FILE.eof() && _lineContent.size()==0);
}



//------------------------------------------------------------------------------
// DESCRIPTION:
//   Rewind function to go back to the beginning of the file.
//   In fact, closes and reopens the file.
void DataFileReader::rewind(void){
  if( _FILE.is_open() ) this->close();  // Closes if already open
  _FILE.open( _filename.c_str() );      // Reopens
  if( !_FILE.is_open() )  abort_program("Could not open file "+_filename);

  _lineNumber      = 0;      // Initializes variables appropriately
  _columnNumber    = 1;
  _numberOfColumns = 0;
 }



#endif // DATAFILEREADER_H
