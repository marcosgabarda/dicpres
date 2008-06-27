#ifndef _LZ77_H
#define _LZ77_H

#include <string>
#include <vector>
#include "types.h"

#define DEFAULT_WINDOW 16

using namespace std;

/**
 * \class LZ77
 *
 * Clase que implementa la compresi&oacute;n de ficheros por el metodo de 
 * diccionario LZ77.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre 
 * \author Marcos Gabarda Inat
 */
class lz77 {

 private:

  /**
   * \var m_vBuffer
   *
   * Buffer que contiene todo el fichero leido
   */
  vector<byte> m_vBuffer;

  /**
   * \var m_iIni
   * \var m_iFin
   *
   * &Iacute;ndices de la ventana de compresi&oacute;n
   */
  int m_iIni, m_iFin;

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

  /**
   * Procesa la siguiente tupla cod77 que se genera en funci&oacute;n de la 
   * posici&oacute;n de la ventana actual.
   */
  cod77 obtenerTupla();

  void readFile (string sFile);

 public:

  lz77(int nVentana = DEFAULT_WINDOW);

  ~lz77();
  
  void compress (string sFileIn, string sFileOut);
  

};

#endif
