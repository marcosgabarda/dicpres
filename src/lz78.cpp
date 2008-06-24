#include "lz78.h"
#include "utils.h"

/**
 * Constructor. Inicializa las variables necesarias para la compresi&oacute;n 
 * din&aacute;mica.
 */
lz78::lz78(){

/**
 * Se inicializan los atributos de la clase:
 *
 * - &Iacute;ndice de compresi&oacute;n.
 *
 * - &Iacute;ndice de relaci&oacute;n entre el mapa y el vector de la clase.
 *
 * - Cuenta del n&uacute;mero de bits necesarios para codificar.
 *
 */
  iComp=-1;
  iIndice=1;
  cuentaIndi=1;
}

/**
 * M&eacute;todo que lee un byte del vBuffer.
 *
 * \param[out] c Byte leido.
 * \return True en caso de que se haya leido un byte correctamente, y false
 * false en caso contrario.
 */
bool lz78::readChar(byte &c){
  int n = static_cast<int>(vBuffer.size());
  iComp++;
  if(n==0 || iComp >= n || iComp < 0) return false;
  c=vBuffer[iComp];
  return true;
}

/**
 * Convierte de un binario, representado por una cadena de caracteres 0 y 1,
 * a un entero, con la codificaci&oacute;n correspondiente en binario real.
 * 
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] sSecuencia string
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
 * cadena de 0s y 1s, con la codificaci&oacute;n correspondiente en binario real
 * de tama&ntilde;o log(cuentaIndi)/log(2) (n&uacute;mero de bits
 * necesarios para codificar el entero).
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] iData int
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
 * M&eacute;todo que lee el fichero a comprimir, y adem&aacute;s contruye el 
 * diccionario inicial.
 *
 * \param[in] sFile Direcci&oacute;n donde se encuentra el fichero a comprimir.
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
 * M&eacute;todo que implementa el algoritmo de copresi&oacute;n.
 *
 * \param[in] sFile Direcci&oacute;n donde se dejar&aacute; el fichero
 * comprimido.
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
	indi = int2bin(0);
      else{
	cadena.pop_back();
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

/**
 * M&eacute;todo que lee el fichero con la informaci&oacute;n comprimida y
 * rellena la tabla con los elementos codificados en formato LZ78.
 *
 * \param[in] sFile Fichero con la informaci&oacute; comprimida.
 */
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

/**
 * M&eacute;todo que recupera una lista de bytes a partir del vector
 * donde est&aacute; almacenada la informaci&oacute; codificada.
 *
 * \param[out] cadena Lista de bytes obtenidos.
 * \param[out] i &Iacute;ndice de acceso al vector de informaci&oacute;.
 */
void lz78::obtainElem(list<byte> &cadena, int &i){
  int indi = static_cast<int>(vTablaCod[i].first);
  if(indi==0){
    cadena.push_back(vTablaCod[i].second);
    return;
  }
  else{
    int nuevoindi= indi-1;
    obtainElem(cadena,nuevoindi);
    cadena.push_back(vTablaCod[i].second);
    return;
  }
}

/**
 * M&eacute;todo que implementa el algoritmo de descopresi&oacute;n.
 *
 * \param[in] sFile Direcci&oacute;n donde se dejar&aacute; el fichero
 * descomprimido.
 */
void lz78::uncompress(string sFile){
  list <byte> cadena;
  ofstream file(sFile.c_str(), ofstream::binary);
  int tamTabla = static_cast<int>(vTablaCod.size());
  for(int i=0; i< tamTabla; i++){
    obtainElem(cadena,i);
    for(list<byte>::iterator it = cadena.begin(); it!=cadena.end(); it++){
      char buffer[1];
      buffer[0]=static_cast<char>(*it);
      file.write(buffer,1);
    }
    cadena.clear();
  }

  file.close();
}

