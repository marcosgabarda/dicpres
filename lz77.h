#ifndef _LZ77_H
#define _LZ77_H

#include <string>
#include <vector>
#include "types.h"

using namespace std;

/**
 * Clase que implementa la compresion de ficheros por el metodo de dicionario
 * LZ77.
 * \author Iv�n Rodriguez Sastre & Marcos Gabarda Inat
 */
class lz77 {
 private:

  /**
   * Buffer que contiene todo el fichero leido
   */
  vector<byte> vBuffer;

  /**
   * �ndices de la ventana de compresi�n
   */
  int iIni, iFin;

  /**
   * Tabla donde se almacena cada una de las entradas de pares codificantes.
   */
  vector<cod77> vTablaCod;

 public:
  lz77(); 
  ~lz77();

  void readFile (string sFile);
  
  

};

#endif
