#ifndef _LZ78_H
#define _LZ78_H

#include "types.h"

using namespace std;

/**
 * \class lz78
 *
 * Clase que implementa la compresi&oacute;n de ficheros por el m&eacute;todo de
 * dicionario LZ78.
 *
 * Se usan los m&eacute;todos:
 * - compress
 * - uncompress
 *
 * Para comprimir y descomprimir, respectivamente.
 *
 * \date Junio 2008
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 */
class lz78 {
 private:

  /**
   * \var vBuffer 
   * Buffer que contiene todo el fichero leido
   */
  vector<byte> vBuffer;

  /**
   * \var iComp
   * &Iacute;ndice de compresi&oacute;n
   */
  int iComp;
  
  /**
   * \var cuentaIndi
   * Cuenta de &iacute;ndices necesaria para la actualizaci&oacute;n din&aacute;mica de bits.
   */
  int cuentaIndi;

  bool readChar(byte &c);

  /**
   * \var vTablaCod 
   * Tabla donde se almacena cada una de las entradas de pares codificantes.
   */
  vector<cod78> vTablaCod;

  /**
   * \var mTablaCod 
   * Mapa donde se almacena una relaci&oacute;n lista de chars - indice.
   * El &iacute;ndice se utilizar&aacute; para acceder al vector vTablaCod sin recorrerlo. 
   */
  map<list<byte>,int> mTablaCod;

  /**
   * \var iIndice 
   * &Iacute;ndice del mapa y del vector
   */
  int iIndice;

  void error(string msg);

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
