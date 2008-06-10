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
  for (unsigned int j = 0; j < iLimit; j++) {
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
  char buffer[1];
  File.read(buffer, 1);
  byte n = static_cast<byte>(buffer[0]);
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

  debug("Escribiendo fichero comprimido...");
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

  debug("Leyendo fichero...");
  
  codw iCodigoAnterior;
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
  iCodigoAnterior = iCodigo;

  while (!fileIn.eof()) {
    iCodigo = readCodw(fileIn);
    if (m_vTablaCod.find(iCodigo) != m_vTablaCod.end()) {
      /**
       * Caso en el que está en la tabla.
       */
      list<byte> lTmp = m_vTablaCod[iCodigo];
      for (list<byte>::iterator it = lTmp.begin();
	   it != lTmp.end();
	   it++) {
	char buffer[1];
	buffer[0] = static_cast<char>(*it);
	fileOut.write(buffer, 1);
      }
      list<byte> lTmp2 = m_vTablaCod[iCodigoAnterior];
      lTmp2.push_back(lTmp.front());
      codw index = static_cast<codw>(m_vTablaCod.size());
      m_vTablaCod[index] = lTmp2;
      m_vTablaCodInv[lTmp2]= index;
    } else {
      /**
       * Caso en el que NO está en la tabla.
       */
      list<byte> lTmp = m_vTablaCod[iCodigoAnterior];
      lTmp.push_back(lTmp.front());
      for (list<byte>::iterator it = lTmp.begin();
	   it != lTmp.end();
	   it++) {
	char buffer[1];
	buffer[0] = static_cast<char>(*it);
	fileOut.write(buffer, 1);
      }
      codw index = static_cast<codw>(m_vTablaCod.size());
      m_vTablaCod[index] = lTmp;
      m_vTablaCodInv[lTmp]= index;
    }
    iCodigoAnterior = iCodigo;
  }
  debug("FIN");

  fileIn.close();
  fileOut.close();
  
  debug("### FIN DESCOMPRESION ###");

}
