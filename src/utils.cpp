#include "utils.h"

/**
 * Convierte de un binario, repersentado por una cadena de caracteres 0 y 1, 
 * a un unsigned char, con la codificacion correspondiente en binario real. 
 * La secuencia tiene que ser exactamente de 8 caracteres.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param sSecuencia string
 * \return unsigned char
 */
byte bin2char(string sSecuencia) {

  if (sSecuencia.size() != 8) return '\0';

  int nLongitud = static_cast<int>(sSecuencia.size());
  byte nSum = 0;
  for (int i = 0; i < nLongitud; i++) {
    unsigned char c = sSecuencia[i];
    int n = 0;
    if (c == '0') {
      n = 0;
    } else if (c == '1'){
      n = 1;
    }    
    nSum += static_cast<unsigned int>(n*pow(2.0, (nLongitud - 1) - i));
  }
  byte cOcteto;
  cOcteto = static_cast<byte>(nSum);
  return cOcteto;
}

/**
 * Convierte de un unsigned char a un binario, representado por una 
 * cadena de 0's y 1's, con la codificacion correspondiente en binario real.
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] cData unsigned char
 * \return string
 */
string char2bin(byte cData) {
  string sBuffer;
  string sBufferFinal;
  if(cData==0){
    for (int i = 0; i < 8; i++ )
      sBufferFinal.push_back('0');
    return sBufferFinal;
  } 
  else{    
    for (byte i = cData; i > 1; i/=2) {
      byte nResto = i%2;
      if (nResto == 0) {
	sBuffer.push_back('0');
      } else {
			  sBuffer.push_back('1');
      }
    }
    sBuffer.push_back('1');    
    int nLongitud = static_cast<int>(sBuffer.size());
    for (int i = 0; i < (8 - nLongitud); i++ ) sBufferFinal.push_back('0');
    for(int i = nLongitud - 1; i >= 0; i-- ) sBufferFinal.push_back(sBuffer[i]);
    return sBufferFinal;
  }
}

/**
 * Convierte de un codigo codw en un vector de bytes
 * usando desplazamientos a derechas. Los vectores de
 * bytes tienen el primer byte que indica el n&uacute;mero de 
 * bytes que hay a continuaci&oacute;n.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] Codigo codw
 * \return vector<byte>
 */
vector<byte> codw2byte(codw Codigo) {
  int n = static_cast<int>(sizeof(codw));
  codw MASK = 0xff;
  vector<byte> vResult(n);
  vector<byte> vResultFinal;
  for (int i = 0; i < n; i++) {
    byte tmp = static_cast<byte>(Codigo & MASK);
    Codigo = Codigo >> 8;
    vResult[n - i - 1] = tmp;
  }
  bool flag = false;
  for (int i = 0; i < n; i++) {
    if (!flag && vResult[i] != 0)
      flag = true;
    if (flag)
      vResultFinal.push_back(vResult[i]);
  }
  byte size = static_cast<byte>(vResultFinal.size());
  vResultFinal.insert(vResultFinal.begin(), size);
  return vResultFinal;  
}

/**
 * Convierte de un vector de bytes en un codw, usando
 * desplazamientos a izquierda. No tiene en cuenta el primer
 * byte que se guarda para indicar el n&uacute;mero de bytes
 * que aparecen a continuaci&oacute;n, y se supone que ya se 
 * ha extraido y el vector que se le pasa por par&aacute;metro
 * esta correctamente montado.
 *
 * \author Iv&aacute;n Rodr&iacute;guez Sastre
 * \author Marcos Gabarda Inat
 * \param[in] Codigo codw
 * \return vector<byte>
 */
codw byte2codw(vector<byte> Codigo) {
  int n = static_cast<int>(Codigo.size());
  codw res = 0;
  for (int i = 0; i < n; i++) {
    res = res << 8;
    res = res | Codigo[i];
  }
  return res;
}
