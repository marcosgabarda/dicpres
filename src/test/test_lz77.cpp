#include "../lz77.h"
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
  lz77 tmp(atoi(argv[1]));
  string sIn(argv[2]);
  string sOut(sIn + ".lz77");
  tmp.compress(sIn, sOut);
  return 0;
}
