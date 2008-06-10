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

  /**
   * Tabla para los 256 bytes posibles
   */
  for (unsigned int j = 0; j < 256; j++) {
    byte i = static_cast<byte>(j);
    codw index = static_cast<codw>(m_vTablaCod.size());
    list<byte> tmp;
    tmp.push_back(i);
    m_vTablaCod[index] = tmp;
    m_vTablaCodInv[tmp] = index;
  }

}

bool lzw::readChar(byte &c) {
  int n = static_cast<int>(m_vBuffer.size());
  m_iComp++;
  if (n == 0 || m_iComp >= n || m_iComp < 0) return false;
  c = m_vBuffer[m_iComp];
  return true;
}

void lzw::writeCodw (ofstream &File, codw Codigo) {
  vector<byte> aux = codw2byte(Codigo);
  int n = static_cast<int>(aux.size());
  for (int i = 0; i < n; i++) {
    char c = static_cast<char>(aux[i]);
    char buffer[1];
    buffer[0] = c ;
    File.write(buffer, 1);
  }
}

codw lzw::readCodw (ifstream &File) {
  int n = sizeof(codw);
  vector<byte> tmp;
  for (int i = 0; i < n; i++) {
    char buffer[1];
    File.read(buffer, 1);
    tmp.push_back(static_cast<byte>(buffer[0]));
  }
  codw cod = byte2codw(tmp);
  return cod;
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
  }

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
  while (readChar(cCaracter)) {
    list<byte> sTmp(sCadena);
    sTmp.push_back(cCaracter);
    if (m_vTablaCodInv.find(sTmp) != m_vTablaCodInv.end()) {
      sCadena = sTmp;
    } else {

      /**
       * Añadir sTmp al diccionario.
       */
      codw index = static_cast<codw>(m_vTablaCod.size());
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

  writeCodw(file, nTabla > 256? nTabla - 256 : 0);

  for(codw index = 256; index < nTabla; index++ ) {
    unsigned int nBytes = static_cast<unsigned int>(m_vTablaCod.find(index)->second.size());
    codw iIndex = m_vTablaCod.find(index)->first;
    writeCodw(file, iIndex);
    writeCodw(file, nBytes);
    for(list<byte>::iterator itList = m_vTablaCod.find(index)->second.begin();
	itList != m_vTablaCod.find(index)->second.end();
	itList++) {
      byte b = *itList;
      char buffer[1];
      buffer[0] = static_cast<char>(b);
      file.write(buffer, 1);
    }
    
  }

  int n = static_cast<int>(vBufferSalida.size());
  for (int i = 0; i < n; i++) {
    writeCodw(file, vBufferSalida[i]);
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
  nSizeTabla = readCodw(fileIn);

  debug("Tam. de la tabla guardado en fichero:");
  debug(nSizeTabla);

  debug("Leyendo tabla...");
  for (unsigned int i = 0; i < nSizeTabla; i++) {
    codw iIndex;
    unsigned int nBytes;
    list<byte> tmp;
    iIndex = readCodw(fileIn);
    nBytes = readCodw(fileIn);
    for (unsigned int j = 0; j < nBytes; j++) {
      byte b;
      char buffer[1];
      fileIn.read(buffer, 1);
      b = static_cast<byte>(buffer[0]);
      tmp.push_back(b);
    }
    m_vTablaCod[iIndex] = tmp;
    m_vTablaCodInv[tmp] = iIndex;
  }
  debug("FIN");

  debug("Tam. de la tabla:");
  debug(static_cast<int>(m_vTablaCod.size()));

  debug("Leyendo fichero...");
  while (!fileIn.eof()) {
    codw iCodigo;
    iCodigo = readCodw(fileIn);
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
