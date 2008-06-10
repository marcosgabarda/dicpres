#include "../lzw.h"

using namespace std;

int main(int argc, char *argv[]) {
  lzw tmp(true);
  string sIn(argv[1]);
  string sOut(sIn + ".out");
  tmp.uncompress(sIn, sOut);
  return 0;
}
