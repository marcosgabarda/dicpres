#include <iostream>
#include "../lz78.h"

using namespace std;

int main(int argc, char **argv){
  lz78 tmp;
  string sIn(argv[1]);
  string sOut(sIn+".lz78");
  tmp.readFile(sIn);
  tmp.compress(sOut);
  return 0;
}
