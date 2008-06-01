#include "lz78.h"

lz78::lz78(){
  iComp=-1;
  iIndice=1;
}

byte lz78::readChar(){
  int n = static_cast<int>(vBuffer.size());
  iComp++;
  if(n==0 || iComp >= n || iComp < 0) return 0;
  return vBuffer[iComp];
}

/**
 * Método que lee el fichero a comprimir, y además contruye el diccionario 
 * inicial.
 * \param sFile Dirección donde se encuentra el fichero a comprimir.
 */
void lz78::readFile(string sFile) {

  ifstream file(sFile.c_str(), ifstream::binary);
  byte cCaracter;
  char buffer[1];

  while (!file.read(buffer, 1).eof()) {
    cCaracter = static_cast<byte>(buffer[0]);
    vBuffer.push_back(cCaracter);
  }

  file.close(); 

}

/**
 * Método que comprime con LZ78.
 * \param sFile Dirección donde se dejara el fichero comprimido.
 */
void lz78::compress(string sFile){
  byte c;
  list<byte> cadena;

  while((c = readChar())){
    cadena.push_back(c);
    if(mTablaCod.find(cadena)==mTablaCod.end()){
      mTablaCod[cadena]=iIndice;
      if(cadena.size()==1)
	vTablaCod.push_back(cod78(0,c));
      else{
	cadena.pop_back();
	vTablaCod.push_back(cod78(mTablaCod[cadena],c));
      }
      iIndice++;
      cadena.clear();
    }
  }
  ofstream file(sFile.c_str(),ofstream::binary);
  for(unsigned int i=0; i< vTablaCod.size(); i++){
    byte indi = static_cast<byte>(vTablaCod[i].first);
    char buffer[2];
    buffer[0]=indi;
    buffer[1]=vTablaCod[i].second;
    file.write(buffer,2);
  }
  file.close();
}