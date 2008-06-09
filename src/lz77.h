#ifndef _LZ77_H
#define _LZ77_H

#include <string>
#include <vector>
#include "types.h"

#define DEFAULT_WINDOW 16

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
  vector<byte> m_vBuffer;

  /**
   * �ndices de la ventana de compresi�n
   */
  int m_iIni, m_iFin;

  /**
   * Tama�o de la ventana
   */
  int m_nVentana;

  /**
   * Tabla donde se almacena cada una de las entradas de pares codificantes.
   */
  vector<cod77> vTablaCod;

  /**
   * Procesa la siguiente tupla cod77 que se genera en funci�n de la posici�n
   * de la ventana actual.
   */
  cod77 obtenerTupla();

 public:

  lz77(int nVentana = DEFAULT_WINDOW);

  ~lz77();

  void readFile (string sFile);
  

};

#endif
