#ifndef _LZW_H
#define _LZW_H

#include "types.h"

using namespace std;

/**
 * \class lzw
 *
 * Clase que implementa la compresi&oacute;n de ficheros por el m&eacute;todo de
 * diccionario LZW.
 *
 * Se usan los m&eacute;todos:
 * - compress
 * - uncompress
 *
 * Para comprimir y descomprimir, respectivamente.
 *
 * \date Julio 2008
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 *
 */
class lzw {
 private:

  /**
   * \var m_vBuffer 
   * Buffer que contiene todo el fichero leido.
   */
  vector<byte> m_vBuffer;

  /**
   * \var m_iComp 
   * &Iacute;ndice de lectura del fichero fuente.
   */
  int m_iComp;

  /**
   * \var m_bVerbose 
   * Variable booleana que indica si se deben de mostrar o no la salida 
   * informada de los pasos que sigue la compilaci&oacute;n.
   */
  bool m_bVerbose;

  /**
   * \var m_vTablaCod 
   * Tabla donde se almacena cada una de las entradas de pares 
   * codificantes.
   */
  map<codw, list<byte> > m_vTablaCod;

  /**
   * \var m_vTablaCodInv
   * Tabla donde se almacena cada una de las entradas de pares 
   * codificantes, pero indexadas a la inversa, para optimizar el acceso a los 
   * elementos de m_vTablaCod.
   */
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
