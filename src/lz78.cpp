#include "lz78.h"
#include "utils.h"

lz78::lz78(){
  iComp=-1;
  iIndice=1;
  cuentaIndi=1;
}

bool lz78::readChar(byte &c){
  int n = static_cast<int>(vBuffer.size());
  iComp++;
  if(n==0 || iComp >= n || iComp < 0) return false;
  c=vBuffer[iComp];
  return true;
}

/**
 * Convierte de un binario, representado por una cadena de caracteres 0 y 1, a un 
 * entero, con la codificacion correspondiente en binario real. 
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param sSecuencia string
 * \return unsigned char
 */
int lz78::bin2int(string sSecuencia) {

  int nLongitud = static_cast<int>(sSecuencia.size());
  int nSum = 0;

  for (int i = 0; i < nLongitud; i++) {
    unsigned char c = sSecuencia[i];
    int n = 0;
    if (c == '0') {
      n = 0;
    } else if (c == '1'){
      n = 1;
    }    
    nSum += static_cast<int>(n*pow(2.0, (static_cast<double>(nLongitud) - 1) - i));
  }

  return nSum;
}

/**
 * Convierte de un unsigned int a un binario, representado por una 
 * cadena de 0's y 1's, con la codificacion correspondiente en binario real
 * de tamaÒo log(cuentaIndi)/log(2) (número de bits
 * necesarios para codificar el entero).
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param iData int
 * \return string
 */
string lz78::int2bin(int iData) {
  string sBuffer;
  string sBufferFinal;
  int nbits = log(cuentaIndi)/log(2);
  nbits=((nbits/8)+1)*8;

  if(iData==0){
    for (int i = 0; i < nbits; i++ )
      sBufferFinal.push_back('0');
    return sBufferFinal;
  }

  else{

    for (int i = iData; i > 1; i/=2) {
      int nResto = i%2;
      if (nResto == 0) {
	sBuffer.push_back('0');
      } else {
	sBuffer.push_back('1');
      }
    }
    sBuffer.push_back('1');
  
    int nLongitud = static_cast<int>(sBuffer.size());
    for (int i = 0; i < (nbits - nLongitud); i++ )
      sBufferFinal.push_back('0');
    for(int i = nLongitud - 1; i >= 0; i-- )
      sBufferFinal.push_back(sBuffer[i]);
    return sBufferFinal;
  }
}


/**
 * M&eacute;todo que lee el fichero a comprimir, y además contruye el diccionario 
 * inicial.
 * \param sFile Direcci&oacute;n donde se encuentra el fichero a comprimir.
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
 * M&eacute;todo que comprime con LZ78.
 * \param sFile Direcci&oacute;n donde se dejara el fichero comprimido.
 */
void lz78::compress(string sFile){
  byte c;
  list<byte> cadena;
  ofstream file(sFile.c_str(),ofstream::binary);
	
  while((readChar(c))){
    cadena.push_back(c);
    if(mTablaCod.find(cadena)==mTablaCod.end()){
      mTablaCod[cadena]=iIndice;
      string indi;
      if(cadena.size()==1)
	//vTablaCod.push_back(cod78(0,c));
	indi = int2bin(0);
      else{
	cadena.pop_back();
	//vTablaCod.push_back(cod78(mTablaCod[cadena],c));
	indi = int2bin(mTablaCod[cadena]);
      }
			
      int nbits=log(cuentaIndi)/log(2);
      nbits=((nbits/8)+1)*8;
      int tambuf=(nbits/8)+1; 
      char *buffer = new char[tambuf];
      for(int j=0, n=0; j < tambuf-1; j++, n+=8){
	buffer[j]= bin2char(indi.substr(n,8));
      }
      buffer[tambuf-1]=c;
      file.write(buffer,tambuf);
			
      iIndice++;
      cuentaIndi++;
      cadena.clear();
      delete []buffer;
    }
  }
	
  file.close();
}

void lz78::readCom(string sFile) {

  ifstream file(sFile.c_str(), ifstream::binary);
  string indichar;
  int indi;

  while (!file.eof()) {
  
    int nbits=log(cuentaIndi)/log(2);
    nbits=((nbits/8)+1)*8;
    int tambuf=(nbits/8)+1; 
    char *buffer = new char[tambuf];
  
    file.read(buffer, tambuf);
    //indi = static_cast<int>(buffer[0]);
    for(int i=0; i < nbits/8; i++){
      byte cara=static_cast<byte>(buffer[i]);
      indichar.append(char2bin(cara));
    }
    //cerr<<indichar<<endl;
    indi=bin2int(indichar);
    indichar.clear();
    //cerr<<indi<<endl;
    vTablaCod.push_back(cod78(indi,buffer[tambuf-1]));
    cuentaIndi++;
    delete []buffer;
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
 * M&eacute;todo que descomprime un fichero LZ78.
 * \param sFile Dirección donde se dejara el fichero descomprimido.
 */
void lz78::uncompress(string sFile){
  list <byte> cadena;
  ofstream file(sFile.c_str(), ofstream::binary);
  //cout<<"Size: "<<vTablaCod.size()<<endl;
  int tamTabla = static_cast<int>(vTablaCod.size());
  for(int i=0; i< tamTabla; i++){
    //cout<<i<<endl;
    //cerr<<"Antes obtain "<<i<<endl;
    obtainElem(cadena,i);
    //cerr<<"Tras obtain "<<i<<endl;
    for(list<byte>::iterator it = cadena.begin(); it!=cadena.end(); it++){
      char buffer[1];
      buffer[0]=static_cast<char>(*it);
      file.write(buffer,1);
    }
    cadena.clear();
  }

  file.close();
}

