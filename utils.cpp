#include <string>
#include "utils.h"

/**
 * Convierte de un binario, repersentado por una cadena de caracteres 0 y 1, a un 
 * unsigned char, con la codificacion correspondiente en binario real. La secuencia
 * tiene que ser exactamente de 8 caracteres.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param sSecuencia string
 * \return unsigned char
 */
unsigned char bin2char(string sSecuencia) {

  if (sSecuencia.size() != 8) return '\0';

  int nLongitud = static_cast<int>(sSecuencia.size());
  unsigned int nSum = 0;
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
  unsigned char cOcteto;
  cOcteto = static_cast<unsigned char>(nSum);
  return cOcteto;
}

/**
 * Convierte de un unsigned char a un binario, representado por una 
 * cadena de 0's y 1's, con la codificacion correspondiente en binario real.
 * \author Iván Rodriguez Sastre & Marcos Gabarda Inat
 * \param cData unsigned char
 * \return string
 */
string char2bin(unsigned char cData) {
  string sBuffer;
  for (unsigned char i = cData; i > 1; i/=2) {
    unsigned char nResto = i%2;
    if (nResto == 0) {
      sBuffer.push_back('0');
    } else {
      sBuffer.push_back('1');
    }
  }
  sBuffer.push_back('1');
  string sBufferFinal;
  int nLongitud = static_cast<int>(sBuffer.size());
  for (int i = 0; i < (8 - nLongitud); i++ ) sBufferFinal.push_back('0');
  for(int i = nLongitud - 1; i >= 0; i-- ) sBufferFinal.push_back(sBuffer[i]);
  return sBufferFinal;
}
