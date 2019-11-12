#include <stdlib.h>

typedef struct Heap {

    int* vetor, n, min;

} Heap;

Heap *criarHeap(){
    Heap *hp = (Heap*) malloc(sizeof(Heap));
    hp->min = 10;
    hp->n = 0;
    hp->vetor = (int*) malloc(sizeof(int) * hp->min);
    return hp;
}

void rise(Heap *hp, int index){

}

void add(Heap *hp, int x){
    hp->vetor[hp->n] = x;
    rise(hp, hp->n++);
}