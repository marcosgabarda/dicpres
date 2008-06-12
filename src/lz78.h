#ifndef _LZ78_H
#define _LZ78_H

#include <string>
#include <vector>
#include "types.h"

using namespace std;

/**
 * Clase que implementa la compresi&oacute;n de ficheros por el metodo de dicionario
 * LZ78.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 */
class lz78 {
 private:

  /**
   * Buffer que contiene todo el fichero leido
   */
  vector<byte> vBuffer;

  /**
   * &Iacute;ndice de compresi&oacute;n
   */
  int iComp;
  
  /**
   * Cuenta de &iacute;ndices necesaria para la actualizaci&oacute;n din&aacute;mica de bits.
   */
  int cuentaIndi;

  bool readChar(byte &c);

  /**
   * Tabla donde se almacena cada una de las entradas de pares codificantes.
   */
  vector<cod78> vTablaCod;

  /**
   * Mapa donde se almacena una relaciÛn lista de chars - indice.
   * El &iacute;ndice se utilizar&aacute; para acceder al vector vTablaCod sin recorrerlo. 
   */
  map<list<byte>,int> mTablaCod;

  /**
   * &Iacute;ndice del mapa y del vector
   */
  int iIndice;

 public:
  lz78(); 
  void readFile (string sFile);
  void compress (string sFile);
  void readCom (string sFile);
  void uncompress (string sFile);
  
  string int2bin(int iData);
  int bin2int(string sSecuencia);

  void obtainElem(list<byte> &cadena, int &i);

};

#endif
