#include "lz78.h"
#include "utils.h"

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
    
    //byte indi = static_cast<byte>(vTablaCod[i].first);
    //cout<<vTablaCod[i].first<<endl;
    string indi = int2bin(vTablaCod[i].first);
    //cout<<"Prueba"<<endl;   
    char buffer[5];
    
    for(int j=0, n=0; j < 32/8; j++, n+=8){
      buffer[j]= bin2char(indi.substr(n,8));
    }
    buffer[4]=vTablaCod[i].second;
    file.write(buffer,5);
  }
  file.close();
}

void lz78::readCom(string sFile) {

  ifstream file(sFile.c_str(), ifstream::binary);
  string indichar;
  int indi;
  char buffer[5];

  while (!file.eof()) {
    file.read(buffer, 5);
    //indi = static_cast<int>(buffer[0]);
    for(int i=0; i < 32/8; i++){
      byte cara=static_cast<byte>(buffer[i]);
      indichar.append(char2bin(cara));
    }
    //cerr<<indichar<<endl;
    indi=bin2int(indichar);
    indichar.clear();
    cerr<<indi<<endl;
    vTablaCod.push_back(cod78(indi,buffer[4]));
  }

  file.close(); 
}

void lz78::obtainElem(list<byte> &cadena, int &i){
  //cerr<<"Obtain "<<i<<endl;
  int indi = static_cast<int>(vTablaCod[i].first);
  if(indi==0){
    //cerr<<"indi 0. i "<<i<<endl;
    cadena.push_back(vTablaCod[i].second);
    return;
  }
  else{
    //cerr<<"indi "<< indi<<". i "<<i<<endl;
	int nuevoindi= indi-1;
    obtainElem(cadena,nuevoindi);
    cadena.push_back(vTablaCod[i].second);
    return;
  }
}

/**
 * Método que descomprime un fichero LZ78.
 * \param sFile Dirección donde se dejara el fichero descomprimido.
 */
void lz78::uncompress(string sFile){
  list <byte> cadena;
  ofstream file(sFile.c_str(), ofstream::binary);
  //cout<<"Size: "<<vTablaCod.size()<<endl;
  int tamTabla = static_cast<int>(vTablaCod.size());
  for(int i=0; i< tamTabla; i++){
    //cout<<i<<endl;
    cerr<<"Antes obtain "<<i<<endl;
    obtainElem(cadena,i);
    cerr<<"Tras obtain "<<i<<endl;
    for(list<byte>::iterator it = cadena.begin(); it!=cadena.end(); it++){
      char buffer[1];
      buffer[0]=static_cast<char>(*it);
      file.write(buffer,1);
    }
    cadena.clear();
  }

  file.close();
}
