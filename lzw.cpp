#include "lzw.h"
#include "utils.h"

lzw::lzw(bool bVerbose) {
  m_iComp = -1;
  m_bVerbose = bVerbose;
}

byte lzw::readChar() {
  int n = static_cast<int>(m_vBuffer.size());
  m_iComp++;
  if (n == 0 || m_iComp >= n || m_iComp < 0) return 0;
  return m_vBuffer[m_iComp];
}

void lzw::debug(const char* buffer) {
  if (m_bVerbose)
    cout << "[Debug] "<< buffer;
}
void lzw::debug(string buffer) {
  if (m_bVerbose)
    cout << "[Debug] "<< buffer << endl;
}

/**
 * Método que lee el fichero a comprimir, y además contruye el diccionario 
 * inicial.
 * \param sFile Dirección donde se encuentra el fichero a comprimir.
 */
void lzw::readFile (string sFile) {
  
  debug(string("Fichero de entrada: ") + sFile );
  ifstream file(sFile.c_str(), ifstream::binary);
  byte cCaracter;
  char buffer[1];

  while (!file.read(buffer, 1).eof()) {
    cCaracter = static_cast<byte>(buffer[0]);
    
    m_vBuffer.push_back(cCaracter);

    list<byte> tmp;
    tmp.push_back(cCaracter);
    
    if (m_vTablaCodInv.find(tmp) == m_vTablaCodInv.end()) {
      codw index = static_cast<codw>(m_vTablaCod.size() + 1);
      m_vTablaCod[index] = tmp;
      m_vTablaCodInv[tmp]= index;
    }
    
  }

  file.close(); 

}

/**
 * Método que comprime.
 * \param sFile Dirección donde se dejara el fichero comprimido.
 */
void lzw::compress (string sFile) {
  
  debug(string("Fichero de salida: ") + sFile );
  ofstream file(sFile.c_str(), ofstream::binary);

  list<byte> sCadena;
  byte cCaracter;
  while ((cCaracter = readChar())) {
    list<byte> sTmp(sCadena);
    sTmp.push_back(cCaracter);
    if (m_vTablaCodInv.find(sTmp) != m_vTablaCodInv.end()) {
      sCadena = sTmp;
    } else {
      /**
       * Añadir sTmp al diccionario.
       */
      codw index = static_cast<codw>(m_vTablaCod.size() + 1);
      m_vTablaCod[index] = sTmp;
      m_vTablaCodInv[sTmp]= index;
      /**
       * Emitir índice de sCadena
       */
      file << m_vTablaCodInv[sCadena];
      
      sCadena.clear();
      sCadena.push_back(cCaracter);

    }
  }
  
  file.close();
  
}
