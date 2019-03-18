#include "List.h"
#include <iostream>

using namespace std;

int main() {
  List<unsigned> list;
  for (unsigned i = 0; i < 9; i++) { list.insertFront(i);}
  list.reverseNth(3);
  list.print(cout);
  return 0;
}
