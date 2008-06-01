#include "lzw.h"
#include "utils.h"

lzw::lzw(bool bVerbose) {
  m_bVerbose = bVerbose;
}

void lzw::init() {
  m_iComp = -1;
  m_vBuffer.clear();
  m_vTablaCod.clear();
  m_vTablaCodInv.clear();
}

byte lzw::readChar() {
  int n = static_cast<int>(m_vBuffer.size());
  m_iComp++;
  if (n == 0 || m_iComp >= n || m_iComp < 0) return 0;
  return m_vBuffer[m_iComp];
}

void lzw::debug(const char* buffer) {
  if (m_bVerbose)
    cout << "[Debug] "<< buffer << endl;
}
void lzw::debug(string buffer) {
  if (m_bVerbose)
    cout << "[Debug] "<< buffer << endl;
}
void lzw::debug(int buffer) {
  if (m_bVerbose)
    cout << "[Debug] "<< buffer << endl;
}

/**
 * Método que lee el fichero a comprimir, y además contruye el diccionario 
 * inicial.
 * \param sFile Dirección donde se encuentra el fichero a comprimir.
 */
void lzw::readSource (string sFile) {

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

  debug(string("Simbolos del diccionario iniciales: "));
  debug(static_cast<int>(m_vTablaCodInv.size()));

  file.close(); 

}

/**
 * Método que comprime.
 * \param sFile Dirección donde se dejara el fichero comprimido.
 */
void lzw::compress (string sFileIn, string sFileOut) {
  
  debug("### INICIO COMPRESION ###");

  debug(string("Fichero de entrada: ") + sFileIn );

  init();

  readSource(sFileIn);

  debug(string("Fichero de salida: ") + sFileOut );
  ofstream file(sFileOut.c_str(), ofstream::binary);
  
  vector<codw> vBufferSalida;

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
      vBufferSalida.push_back(m_vTablaCodInv[sCadena]);
      
      sCadena.clear();
      sCadena.push_back(cCaracter);

    }
  }

  debug(string("Simbolos del diccionario tras comprimir: "));

  unsigned int nTabla = static_cast<unsigned int>(m_vTablaCod.size());
  debug(nTabla);

  file << nTabla << " ";
  for(map<codw, list<byte> >::iterator itTabla = m_vTablaCod.begin();
      itTabla != m_vTablaCod.end();
      itTabla++) {
    unsigned int nBytes = static_cast<unsigned int>(itTabla->second.size());
    codw iIndex = itTabla->first;
    file << iIndex;
    file << nBytes;
    for(list<byte>::iterator itList = itTabla->second.begin();
	itList != itTabla->second.end();
	itList++) {
      byte b = *itList;
      file << b;
    }
    
  }

  int n = static_cast<int>(vBufferSalida.size());
  for (int i = 0; i < n; i++) {
    file << vBufferSalida[i];
  }

  file.close();

  debug("### FIN COMPRESION ###");
  
}

void lzw::uncompress (string sFileIn, string sFileOut) {
  
  debug("### INICIO DESCOMPRESION ###");

  init();

  ifstream fileIn(sFileIn.c_str(), ifstream::binary);
  ofstream fileOut(sFileOut.c_str(), ofstream::binary);

  /**
   * Leer la tabla de compresion.
   */
  unsigned int nSizeTabla;
  fileIn >> nSizeTabla;

  debug("Tam. de la tabla:");
  debug(nSizeTabla);

  debug("Leyendo tabla...");
  for (unsigned int i = 0; i < nSizeTabla; i++) {
    codw iIndex;
    unsigned int nBytes;
    list<byte> tmp;
    fileIn >> iIndex;
    fileIn >> nBytes;
    for (unsigned int j = 0; j < nBytes; j++) {
      byte b;
      fileIn >> b;
      tmp.push_back(b);
    }
    m_vTablaCod[iIndex] = tmp;
    m_vTablaCodInv[tmp] = iIndex;
  }
  debug("FIN");

  debug("Leyendo fichero...");
  while(!fileIn.eof()) {
    codw iCodigo;
    fileIn >> iCodigo;
    list<byte> lTmp = m_vTablaCod[iCodigo];
    for (list<byte>::iterator it = lTmp.begin();
	 it != lTmp.end();
	 it++) {
      char buffer[1];
      buffer[0] = static_cast<char>(*it);
      fileOut.write(buffer, 1);
    }
  }
  debug("FIN");

  fileIn.close();
  fileOut.close();
  
  debug("### FIN DESCOMPRESION ###");

}
