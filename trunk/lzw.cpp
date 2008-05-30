#include "lzw.h"

/**
 * Método que lee el fichero a comprimir, y además contruye el diccionario 
 * inicial.
 */
void lzw::readFile(string sFile) {

  ifstream file(sFile.c_str(), ifstream::binary);
  byte cCaracter;
  char buffer[1];

  while (!file.read(buffer, 1).eof()) {
    cCaracter = static_cast<byte>(buffer[0]);
    
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
