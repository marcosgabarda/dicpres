#include "lz77.h"

/**
 * Constructor de la clase lz77. Si no se le especifica el tama&ntilde;o
 * de ventana, se tomar&aacute; una ventana de 16 bytes.
 *
 * \param[in] nVentana Tama&ntilde;o de la ventana.
 */
lz77::lz77(int nVentana) {
  m_nVentana = nVentana;
  m_iIni = 0;
  m_iFin = nVentana - 1;
}

/**
 * Leer un fichero de fuente.
 *
 * \param[in] sFile Direcci&oacute;n del fichero fuente que va a leer.
 */
void lz77::readFile(string sFile) {

  ifstream file(sFile.c_str(), ifstream::binary);
  byte cCaracter;
  char buffer[1];

  while (!file.read(buffer, 1).eof()) {
    cCaracter = static_cast<byte>(buffer[0]);
    m_vBuffer.push_back(cCaracter);
  }

  file.close(); 

}

/**
 * M&eacute;todo que implementa el algoritmo de compresi&oacute;n.
 * 
 * \param[in] sFileIn Direcci&oacute;n del fichero fuente.
 * \param[in] sFileOut Direcci&oacute;n del fichero destino.
 *
 */
void lz77::compress (string sFileIn, string sFileOut) {
  
  ofstream file(sFileOut.c_str(), ofstream::binary);

  readFile(sFileIn);

  unsigned int nBuffer = static_cast<unsigned int>(m_vBuffer.size());
  
  char tmp = static_cast<char>(nBuffer);
  char buffer[1];
  buffer[0] = tmp;
  file.write(buffer, 1);

  /**
   * Primera fase. Creaci&oacute;n de la ventana inicial de 
   * busqueda.
   */
  unsigned int i;
  for (i = m_iIni; i < static_cast<unsigned int>(m_nVentana) && i < nBuffer; i++) {    
    char tmp = static_cast<char>(m_vBuffer[i]);
    char buffer[1];
    buffer[0] = tmp;
    file.write(buffer, 1);
  }
  if ( i == nBuffer) return;

  /**
   * Segunda parte.
   */
  for ( i = m_iFin + 1; i < nBuffer; i++) {
    byte c = m_vBuffer[i];

    unsigned int iIndex = m_iIni;
    unsigned int iIndex_tmp = m_iIni;

    unsigned int d = 0;
    unsigned int tam = 0;

    while (iIndex_tmp <= m_iFin) {
      
      unsigned int i_tmp = i + 1;
      
      /**
       * Se busca la primera coincidencia del siguiente caracter a comprimir
       * dentro del buffer de b&uacute;squeda.
       */
      for (iIndex = iIndex_tmp ; iIndex < static_cast<unsigned int>(m_iFin); iIndex++) {
	if (m_vBuffer[iIndex] == c) {
	  break;
	}
      }
      if (iIndex == static_cast<unsigned int>(m_iFin)) break;

      iIndex_tmp = iIndex;
      unsigned int d_tmp = iIndex - m_iIni;

      /**
       * Se busca la primera diferencia, que indicar&aacute; el final del prefijo
       * m&aacute;s largo encontrado.
       */
      for (iIndex = m_iIni + d_tmp; iIndex < nBuffer; iIndex++, i_tmp++) {
	c = m_vBuffer[i_tmp];
	if (m_vBuffer[iIndex] != c) {
	  break;
	}
      }
      unsigned int tam_tmp = iIndex - (m_iIni + d_tmp);      

      /**
       * M&aacute;ximo tama&ntilde;o de prefijo.
       */
      if (tam_tmp > tam) {
	tam = tam_tmp + 1;
	d = d_tmp - 1;
	i = i_tmp;
      }
    }      

    cod77 aux = pair<pair<unsigned int, unsigned int>, byte>(pair<unsigned int, unsigned int>(d, tam),c);

    /**
     * Escribir la tupla del lz77 en el fichero de salida.
     */     
    char buffer[3];
    buffer[0] = static_cast<char>(d);
    buffer[1] = static_cast<char>(tam);
    buffer[2] = static_cast<char>(c);
    file.write(buffer, 3);
    
    /**
     * Actualizamos la posici&oacute;n de la ventana.
     */
    m_iFin = i;
    m_iIni = m_iFin - (m_nVentana - 1);
  }

  file.close();
}
