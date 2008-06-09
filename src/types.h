#ifndef _TYPES_H_
#define _TYPES_H_

#include <map>
#include <list>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned char byte;

/**
 * Codificación del LZ77
 * Se corresponde con la tripleta: (d, |x|, cod(a))
 */
typedef pair<pair<int, int>, byte> cod77; 

/**
 * Codificación del LZ78
 * Se corresponde con el par: (i, cod(a))
 *
 * NOTA: Si i == 0, entonces no hay que referenciar a ninguna posición
 * de la tabla.
 */
typedef pair<int, byte> cod78;

/**
 * Codificación del LZW
 * Se corresponde con la tripleta: (i, cod(a))
 */
typedef unsigned int codw; 


#endif
