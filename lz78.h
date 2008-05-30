#ifndef _LZ78_H
#define _LZ78_H

#include <string>
#include <vector>
#include "types.h"

using namespace std;

/**
 * Clase que implementa la compresion de ficheros por el metodo de dicionario
 * LZ78.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 */
class lz78 {
 private:

  /**
   * Buffer que contiene todo el fichero leido
   */
  vector<byte> vBuffer;

  /**
   * Índice de compresión
   */
  int iComp;


  /**
   * Tabla donde se almacena cada una de las entradas de pares codificantes.
   */
  vector<cod78> vTablaCod;

 public:
  lz78(); 
  ~lz78();

  void readFile (string sFile);

};

#endif
