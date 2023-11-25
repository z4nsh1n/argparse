#include "argparse.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct Arg {
  Type type;
  const char *lng;
  char shrt;
  const char *help;
  union {
    char *str;
    int i;
    float f;
    double d;
    int opt;
  } data;
} Arg;


//static Arg *args = NULL;
struct ArgList {
  size_t counter;
  Arg **args;
  char *cmd_name;
};

Arg *argFindByLong(ArgPtr p, const char *name);
Arg *argFindByShort(ArgPtr p, const char c);
void argPrint(ArgPtr p);

ArgPtr argInit(){
  struct ArgList *lst = malloc(sizeof(struct ArgList));
  lst->args = malloc(sizeof(Arg*)*255);
  lst->counter = 0;
  lst->cmd_name = "command";
  return lst;
}

void argUsage(ArgPtr p) {
  printf("%s [Options]\n", p->cmd_name);
  argPrint(p);

}
void argParse(ArgPtr p, int argc, char **argv){
  // skip command name
  p->cmd_name = argv[0];
  int count = 1;

  while(count < argc) {
    if ( strncmp(argv[count], "--", 2) == 0 ) {
      //printf("FLAG: %s\n", argv[count]);
    //search long flag
      Arg *a = argFindByLong(p, (argv[count])+2);
      // assert(a);
      // Handle unknown flags
      if (a == NULL) {
        argUsage(p);
        return;
      }
      switch (a->type) {
        case Option: 
          a->data.opt = 1;
          break;
        case String:
          count++;
          assert(count < argc);
          a->data.str = argv[count];
          break;
        case Int:
          count++;
          assert(count < argc);
          a->data.i = strtol(argv[count], NULL, 10);
          break;
        case Float:
          count++;
          a->data.f = strtof(argv[count], NULL);
          break;
        case Double:
          count++;
          a->data.d = strtod(argv[count], NULL);
          break;
      }
    } else if ( strncmp(argv[count], "-", 1) == 0 ) {
      Arg *a = argFindByShort(p, *((argv[count])+1));
      //assert(a);
      // Handle unknown flags
      if (a == NULL) {
        argUsage(p);
        return;
      }
      switch (a->type) {
        case Option: 
          a->data.opt = 1;
          break;
        case String:
          count++;
          assert(count < argc);
          a->data.str = argv[count];
          break;
        case Int:
          count++;
          assert(count < argc);
          a->data.i = strtol(argv[count], NULL, 10);
          break;
        case Float:
          count++;
          a->data.f = strtof(argv[count], NULL);
          break;
        case Double:
          count++;
          a->data.d = strtod(argv[count], NULL);
          break;
      }
    }
    count++;
  }
}

Arg *argFindByShort(ArgPtr p, const char c){
  for (int i=0; i<p->counter; i++) {
    if ( p->args[i]->shrt == c ) {
      return p->args[i];
    }
  }
  return NULL;
}
Arg *argFindByLong(ArgPtr p, const char *name){
  for (int i=0; i<p->counter; i++) {
    if ( strcmp(p->args[i]->lng, name) == 0 ) {
      return p->args[i];
    }
  }
  return NULL;
}

int *argLngGetOpt(ArgPtr p, const char *lng){
  Arg *a = argFindByLong(p, lng);
  if (  a != NULL ) {
    //return (int *) &a->data; ????
    return (int *) &a->data.opt;
  }
  return NULL;
}
char *argLngGetStr(ArgPtr p, const char *lng){
  Arg *a = argFindByLong(p, lng);
  if (  a != NULL ) {
    //return (int *) &a->data; ????
    return (char *) a->data.str;
  }
  return NULL;
}

double *argLngGetDouble(ArgPtr p, const char *lng){
  Arg *a = argFindByLong(p, lng);
  if (  a != NULL ) {
    //return (int *) &a->data; ????
    return (double*) &a->data.d;
  }
  return NULL;
}
float *argLngGetFloat(ArgPtr p, const char *lng){
  Arg *a = argFindByLong(p, lng);
  if (  a != NULL ) {
    //return (int *) &a->data; ????
    return (float*) &a->data.f;
  }
  return NULL;

}
int *argLngGetInt(ArgPtr p, const char *lng){
  Arg *a = argFindByLong(p, lng);
  if (  a != NULL ) {
    //return (int *) &a->data; ????
    return (int *) &a->data.i;
  }
  return NULL;
}
void argPrint(ArgPtr p) {
  for (size_t i=0; i<p->counter; i++) {
    printf("  -%c --%s %s\n", p->args[i]->shrt, p->args[i]->lng, p->args[i]->help);
    //printf("    %s\n", p->args[i]->help);
  }
}

void argAdd(ArgPtr p, const char shrt, const char *lng, Type type, const char *help){
  Arg *a = malloc(sizeof(Arg));
  //*(p->args + p->counter) = a;
  p->args[p->counter] = a;
  a->shrt = shrt;
  a->lng = lng;
  a->type = type;
  if (help) {
    a->help = help;
  } else {
    a->help = "";
  }
  switch (type)
  {
    case Int:
      a->data.i = 0;
      break;
    case String:
      a->data.str ="";
      break;
    case Float:
      a->data.f = 0.0;
      break;
    case Double:
      a->data.d = 0.0;
      break;
    case Option:
      a->data.opt = 0;
      break;
  }

  p->counter += 1;

}

