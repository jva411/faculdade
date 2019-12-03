#ifndef DEFINED_HashTable2
#define DEFINED_HashTable2

#include <stdlib.h>
#include "Generic.h"

typedef struct HashTable_Node{
    Generic *key, *value;
} HashTable_Node;

typedef struct HashTable{

    HashTable_Node* *vetor;
    int size, max, min;
    float coef1, coef2;

    void (*put)(Generic *, Generic *);
    Generic *(*get)(Generic *);

} HashTable;

HashTable *criarHashTable();

#endif