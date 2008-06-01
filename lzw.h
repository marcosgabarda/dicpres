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

  byte readChar();

  void debug(const char* buffer);
  void debug(string buffer);

 public:
  
  lzw(bool bVerbose = false); 

  void readFile (string sFile);
  void compress (string sFile);

};

#endif
