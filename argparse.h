#ifndef ARGPARSE_H_
#define ARGPARSE_H_

typedef enum Type {
  String,
  Int,
  Float,
  Double,
  Option,
} Type;

typedef struct ArgList *ArgPtr;

ArgPtr argInit();
void argParse(ArgPtr p, int argc, char **argv);
void argAdd(ArgPtr p, const char shrt, const char *lng, Type type, const char* help);

int *argLngGetInt(ArgPtr p, const char *lng);
int *argShrtGetInt(ArgPtr p, const char shrt);

float *argLngGetFloat(ArgPtr p, const char *lng);
float *argShrtGetFloat(ArgPtr p, const char shrt);

double *argLngGetDouble(ArgPtr p, const char *lng);
double *argShrtGetDouble(ArgPtr p, const char shrt);

char *argLngGetStr(ArgPtr p, const char *lng);
char *argShrtGetStr(ArgPtr p, const char shrt);

int *argLngGetOpt(ArgPtr p, const char *lng);
int *argShrtGetOpt(ArgPtr p, const char shrt);

void argUsage(ArgPtr p);

#endif
