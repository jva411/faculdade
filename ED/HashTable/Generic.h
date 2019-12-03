#ifndef DEFINED_Generic
#define DEFINED_Generic

#include <stdlib.h>

typedef struct Generic Generic;

struct Generic{
    
    void *p;
    int size;

    int (*equals)(Generic *);

};

Generic *criarGeneric(void *, int);

#endif