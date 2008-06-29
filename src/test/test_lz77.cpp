#include "../lz77.h"

using namespace std;

int main(int argc, char *argv[]) {
  lz77 tmp(32);
  string sIn(argv[1]);
  string sOut(sIn + ".lz77");
  tmp.compress(sIn, sOut);
  return 0;
}
