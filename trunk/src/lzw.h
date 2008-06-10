#ifndef _LZW_H
#define _LZW_H

#include <string>
#include <vector>
#include "types.h"

using namespace std;

/**
 * Clase que implementa la compresion de ficheros por el metodo de dicionario
 * LZW.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 */
class lzw {
 private:

  /**
   * Buffer que contiene todo el fichero leido
   */
  vector<byte> m_vBuffer;

  /**
   * Índice de compresión
   */
  int m_iComp;


  bool m_bVerbose;

  /**
   * Tabla donde se almacena cada una de las entradas de pares codificantes.
   */
  map<codw, list<byte> > m_vTablaCod;
  map<list<byte>, codw> m_vTablaCodInv;

  void init();

  bool readChar(byte &c);
  void readSource (string sFile);

  codw readCodw (ifstream &File);
  void writeCodw (ofstream &File, codw Codigo);

  void debug(const char* buffer);
  void debug(string buffer);
  void debug(int buffer);

  static const unsigned int iLimit = 256;

 public:
  
  lzw(bool bVerbose = false); 

  void compress (string sFileIn, string sFileOut);
  void uncompress (string sFileIn, string sFileOut);

};

#endif
