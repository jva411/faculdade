#ifndef DEFINED_Heap
#define DEFINED_Heap

typedef struct Heap Heap;

struct Heap{

    int* vetor;
    unsigned int size, max;

};

Heap *newHeap();
void Heap_add(Heap *, int);
int Heap_removeMax(Heap *);
char Heap_hasKey(Heap *, int key);

#endif