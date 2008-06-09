#ifndef _UTILS_
#define _UTILS_

#include "types.h"

byte bin2char(string sSecuencia);
string char2bin(byte cData);

int bin2int(string sSecuencia);
string int2bin(int iData);

vector<byte> codw2byte(codw Codigo);
codw byte2codw(vector<byte> Codigo);

#endif
