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
  
  file << nBuffer;

  /**
   * Primera fase. Creaci&oacute;n de la ventana inicial de 
   * busqueda.
   */
  for (int i = m_iIni; i < m_nVentana && i < nBuffer; i++) {    
    char tmp = static_cast<char>(m_vBuffer[i]);
    char buffer[1];
    buffer[0] = tmp;
    file.write(buffer, 1);
  }
  if ( i == nBuffer) return;

  for (int i = m_iFin + 1; i < nBuffer; i++) {
    byte c = m_vBuffer[i];
    if (c != m_vBuffer[i - m_nVentana]) {
      unsigned int tam =;
      unsigned int d =;
      cod77 aux = pair(pair(d,tam),c);
      
      /**
       * \todo Emitir aux.
       */
      
      m_iIni += 1;
      m_iFin += 1;
    } else {
    }      
    
  }

  while (m_iFin + 1 < nBuffer) {

    byte c = m_vBuffer[m_iFin + 1];

    for (int i = m_iIni; ; ) {
      if (m_vBuffer[i] != c) {      
	unsigned int tam = i - m_iIni;
	unsigned int d = m_iIni;
	cod77 aux = pair(pair(d,tam),c);

	/**
	 * \todo Emitir aux.
	 */

	m_iIni += 1;
	m_iFin += 1;
	break;
      } else {
	m_iIni++;
	m_iFin++;
      }
      i = m_iIni;
    }
  }

}
