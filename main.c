#include <stdio.h>
#include "argparse.h"

int main(int argc, char *argv[]) {
  ArgPtr a = argInit();

  for (int i=0; i<argc; i++) {
    argAdd(a, 'q', "qwt", Int, "Set Integer for test");
    argAdd(a, 'a', "add", String, "Add todo item with title");
    argAdd(a, 'k', "toggle", Option, "Toggle list view");
    argAdd(a, 'f', "fl", Float, "float value for nothing");
    argAdd(a, 'd', "dl", Double, "float value for nothing");
  }

  argParse(a, argc, argv);
  argUsage(a);

  int *ip = argLngGetInt(a, "qwt");
  char *sp = argLngGetStr(a, "add");
  int *b = argLngGetOpt(a, "toggle");
  float *f = argLngGetFloat(a, "fl");
  double *d = argLngGetDouble(a, "dl");
    
  printf("Get value of qwt: %d\n", *ip);
  printf("Get value of add: %s\n", sp);
  printf("Get value of toggle: %d\n", *b);
  printf("Get value of float: %f\n", *f);
  printf("Get value of double: %e\n", *d);
  printf("Get value of double: %lf\n", *d);
  printf("Get value of double: %g\n", *d);
}
