#ifndef _LZ77_H
#define _LZ77_H

#include "types.h"

/**
 * \def DEFAULT_WINDOW
 * Tama&ntilde;o de ventana por defecto de 16 bytes.
 */
#define DEFAULT_WINDOW 16

using namespace std;

/**
 * \class lz77
 *
 * Clase que implementa la compresi&oacute;n de ficheros por el metodo de 
 * diccionario LZ77. Este metodo de compresi&oacute;n no se ha a&ntilde;adido
 * al programa principal, ya que falta implementar el m&eacute;todo de
 * descompresi&oacute;n. Para realizar pruebas de compresi&oacute;n se
 * recomienda usar el programa de test: test_lz77.
 *
 * \date Junio 2008
 * \author Iv&aacute;n Rodr&iacute;guez Sastre 
 * \author Marcos Gabarda Inat
 */
class lz77 {

 private:

  /**
   * \var m_vBuffer
   *
   * Buffer que contiene todo el fichero leido.
   */
  vector<byte> m_vBuffer;

  /**
   * \var m_iIni
   *
   * &Iacute;ndices inicial de la ventana de compresi&oacute;n.
   */
  int m_iIni;

  /**
   * \var m_iFin
   *
   * &Iacute;ndices final de la ventana de compresi&oacute;n.
   */
  int m_iFin;

  /**
   * \var m_nVentana
   *
   * Tama&ntilde;o de la ventana
   */
  int m_nVentana;

  /**
   * \var m_vTablaCod
   *
   * Tabla donde se almacena cada una de las entradas de pares codificantes.
   */
  vector<cod77> m_vTablaCod;

  void readFile (string sFile);
  void writeCod77(ofstream &File, cod77 Codigo);

  void error(string msg);

 public:

  lz77(int nVentana = DEFAULT_WINDOW);
  
  void compress (string sFileIn, string sFileOut);
  void uncompress (string sFileIn, string sFileOut);

};

#endif
