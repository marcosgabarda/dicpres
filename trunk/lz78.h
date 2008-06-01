#ifndef _LZ78_H
#define _LZ78_H

#include <string>
#include <vector>
#include "types.h"

using namespace std;

/**
 * Clase que implementa la compresion de ficheros por el metodo de dicionario
 * LZ78.
 * \author Iv�n Rodriguez Sastre & Marcos Gabarda Inat
 */
class lz78 {
 private:

  /**
   * Buffer que contiene todo el fichero leido
   */
  vector<byte> vBuffer;

  /**
   * �ndice de compresi�n
   */
  int iComp;

  byte readChar();

  /**
   * Tabla donde se almacena cada una de las entradas de pares codificantes.
   */
  vector<cod78> vTablaCod;

  /**
   * Mapa donde se almacena una relaci�n lista de chars - indice.
   * El �ndice se utilizar� para acceder al vector vTablaCod sin recorrerlo. 
   */
  map<list<byte>,int> mTablaCod;

  /**
   * �ndice del mapa y del vector
   */
  int iIndice;

 public:
  lz78(); 
  void readFile (string sFile);
  void compress (string sFile);

};

#endif
