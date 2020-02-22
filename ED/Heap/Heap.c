#include "Heap.h"

#pragma region TEMP_DEFINEDS

#define HEAP_MIN_SIZE (10)
#define HEAP_COEFFICIENT_1 (1.2)
#define HEAP_COEFFICIENT_2 (5)
#define HEAP_RESIZE_CONDITION_1 ()
#define HEAP_LEFT(INDEX) (1+(INDEX<<1))
#define HEAP_RIGHT(INDEX) ((++INDEX)<<1)
#define HEAP_DAD(INDEX) (INDEX>>1)

#pragma endregion

#pragma region FUNCTIONS_DECLARATION

void rise(Heap *, int);
void fall(Heap *, int);

#pragma endregion

Heap *newHeap(){

    Heap *this = (Heap *) malloc(sizeof(Heap));
    this->size = 0;
    this->max = HEAP_MIN_SIZE;
    this->vetor = (int*) malloc(sizeof(int) * HEAP_MIN_SIZE);
    return this;

}

void Heap_add(Heap *this, int key){

    this->vetor[this->size] = key;
    rise(this, this->size++);

}

int Heap_removeMax(Heap *this){
    
    if(this->size==0) return 0;
    int key = this->vetor[0];
    this->vetor[0] = this->vetor[--this->size];
    fall(this->vetor[0]);
    return key;

}

void rise(Heap *this, int index){

    if(index >= this->size) return;
    int dad = HEAP_DAD(index);
    while(index && this->vetor[index] > this->vetor[dad]){
        int temp = this->vetor[index];
        this->vetor[index] = this->vetor[dad];
        this->vetor[dad] = temp;
        index = dad;
        dad = HEAP_DAD(dad);
    }

}

void fall(Heap *this, int index){

    int esq = HEAP_LEFT(index);
    while(esq < this->size){
        int maior = index;
        if(this->vetor[esq] > this->vetor[maior]) maior = esq;
        int dir = esq+1;
        if(dir != this->size && this->vetor[dir] > this->vetor[maior]) maior = dir;
        if(maior == index) break;
        dir = this->vetor[maior];
        this->vetor[maior] =this->vetor[index];
        this->vetor[index] = dir;
        index = maior;
        esq = HEAP_LEFT(index);
    }

}