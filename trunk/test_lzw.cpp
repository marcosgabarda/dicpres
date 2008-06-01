#include "lzw.h"

using namespace std;

int main(int argc, char *argv[]) {
  lzw tmp;
  string sIn(argv[1]);
  string sOut(sIn + ".lzw");
  tmp.readFile(sIn);
  tmp.compress(sOut);
  return 0;
}
