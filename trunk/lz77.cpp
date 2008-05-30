#include "lz77.h"

void lz77::readFile(string sFile) {

  ifstream file(sFile.c_str(), ifstream::binary);
  byte cCaracter;
  char buffer[1];

  while (!file.read(buffer, 1).eof()) {
    cCaracter = static_cast<byte>(buffer[0]);
    vBuffer.push_back(cCaracter);
  }

  file.close(); 

}
