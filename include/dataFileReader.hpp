//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
// Classe DataFileReader
//
//    Esta classe faz uma interface adequada para ler arquivos de dados.
//    Ignora comentarios e informa o numero da linha e da coluna que se esta
//  lendo, o numero de colunas daquela linha, entre outras coisas.
//________________________________________________________
// PARA FAZER:
//    sobrecarregar o operador --
//________________________________________________________
//A.Z. - 01/06 => Criacao
//       01/06 => Sobrecarreguei o operador +=
//       02/06 => Corrigi o bug que fazia com que a classe retornasse eof se
//                nao tivesse sido dado enter no final da ultima linha de
//                dados. Veja o programa de exemplo dfr2.cpp
//       10/07 => Funcao readColumn pega direto o valor que estah numa dada
//                coluna sem ficar incrementando como antes.
//                Eh mais eficiente que usar o >> varias vezes ateh alcancar a
//                coluna no stream.
//       10/07 => O operador >> usa a funcao readColumn. Assim, ganho bastante
//                em eficiencia porque nao eh preciso dar o loop de antes.
//       10/07 => Funcao seteol pra dizer pra classe que jah leu tudo que queria
//                na linha e supostamente jah chegou ao fim (end of line). Deve
//                ser usada em conjunto com a funcao readColumn.
//T.R  - 11/07 => Tiago Ribeiro: Funcao rewind
//A.Z  - 11/07 => Algumas adaptacoes pequenas na funcao rewind
//       11/07 => Construtor usa funcao rewind
//       02/08 => Deixei de ler a primeira linha automanticamente. Isso
//                simplificou um monte o código eliminando totalmente a
//                necessidade de um marcador de fim de linha -- eol !!
//       02/08 => operator++ retorna booleano dizendo se jah atingiu fim do
//                arquivo ou nao. A movimentacao direta no arquivo eh muito
//                simples porque agora soh precisa de um while( !++dfr ){ ... }
//       03/08 => Metodo template readColumn chamando com template antes por
//                causa do gcc 3.X
//       08/08 => Mensagem de erro mais útil na funcao readColumn()
//       07/11 => Função set para poder usar o objeto com mais de um arquivo
//       11/13 => Mudei o nome de set para open, mais óbvio!
//=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|
#ifndef DATAFILEREADER_H
#define DATAFILEREADER_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "aborta.hpp"
#include "numeros.hpp"
#include "meusTipos.hpp"
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

  bool operator++();     // Pre-incremento

  const DataFileReader &operator += ( MTci &n ){
    for( int i=0; i<n; i++ ) ++(*this);
    return (*this);   // Permite a concatenacao
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
// DESCRICAO:
//   Construtor
DataFileReader::DataFileReader( MTcs &file, MTcs &cs ){
  this->open(file,cs);
}





//------------------------------------------------------------------------------
// DESCRICAO:
//   Função set, para iniciar a leitura de um arquivo
//   Com ela eu não preciso instanciar um objeto para cada arquivo que quero
//  ler, basta dar um set( nome_do_arquivo) e ler
void DataFileReader::open( MTcs &file, MTcs &cs ){
  _commentarySymbol = cs;
  _filename=file;
  this->rewind(); // Vai pro inicio do arquivo e inicia as variaveis apropriadas
}



//------------------------------------------------------------------------------
// DESCRICAO:
//   Vai direto a coluna numero C e pega o valor lah.
//   Se nao tiver a coluna no arquivo, aborta.
// RECEBE:
//   Numero da coluna
// RETORNA:
//   Valor na coluna
template<class T>
T DataFileReader::readColumn( MTci &C ){
  if(C<1){
    aborta("As colunas são numeradas a partir de 1!");
  }
  if(C>_numberOfColumns){
    string msg="A linha "+ntos(_lineNumber)+" nao tem a coluna "+ntos(C)+".";
    msg+=" Nesta linha, as colunas sao numeradas de 1 ateh ";
    msg+=ntos(_numberOfColumns);
    aborta(msg);
  }
  T v;
  stringstream ss( _lineContent[ std::size_t(C-1)] );
  ss >> v;
  return v;
}



//------------------------------------------------------------------------------
// DESCRICAO:
//   Sobrecarga do operador >> para inteiros
template<class T>
DataFileReader &operator >> ( DataFileReader &s, T &v ){

  // Pega o conteudo da coluna especifica
  v = s.template readColumn<T>(s._columnNumber);

  // Incrementa a posicao na linha. Se chegou ao fim, volta ao comeco
  s._columnNumber++;
  if( s._columnNumber == (s._numberOfColumns+1) ) s._columnNumber = 1;

  return s;
}



//------------------------------------------------------------------------------
// DESCRICAO:
//   Pre-incremento
bool DataFileReader::operator++(){

  string saux1,saux2;
  _columnNumber = 1;
  _lineContent  = MTvs();
  while(  _lineContent.empty() && !_FILE.eof() ){

    // Le a linha inteira
    _lineNumber++;
    string completeLine;
    getline( _FILE, completeLine );


    // Posicao do comentario, se existir
    unsigned int p = completeLine.find(_commentarySymbol);


    // Le somente a parte que nao esta comentada
    //if( p != string::npos )    // Tem comentario na linha
      saux1.assign( completeLine, 0, p );
    //else                      // Nao tem comentario na linha
      //saux1.assign( completeLine );


    // Inicializa o vector _lineContent
    stringstream ssaux(saux1);
    while( ssaux >> saux2 ) _lineContent.push_back(saux2);
    _numberOfColumns = _lineContent.size();
  }

  // Fenomenal!
  // Com este teste dah pra ler ateh o final dos arquivos de dados, estando
  // EOF na linha de dados ou em uma nova linha.
  // Nao eh preciso se preocupar em dizer se jah leu tudo o que queria no
  // arquivo ou nao! Massa!
  return (_FILE.eof() && _lineContent.size()==0);
}



//------------------------------------------------------------------------------
// DESCRICAO:
//   Funcao escrita pelo Tiago pra voltar o leitor ao inicio do arquivo.
//   Na verdade, fecha e reabre o arquivo.
void DataFileReader::rewind(void){
  if( _FILE.is_open() ) this->close();  // Fecha se jah estiver aberto
  _FILE.open( _filename.c_str() );      // Reabre
  if( !_FILE.is_open() )  aborta("Nao foi possivel abrir o arquivo "+_filename);

  _lineNumber      = 0;      // Inicializa as variaveis apropriadamente
  _columnNumber    = 1;
  _numberOfColumns = 0;
 }



#endif // DATAFILEREADER_H
