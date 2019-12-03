#include "HashTable2.h"

HashTable *this;

int hash(Generic *key){
    int *p = (int *) key->p, size = key->size, i = 0, hash = 0;
    while(size>0){
        hash = hash*8193 + p[i++]*8193;
        size -= sizeof(int);
    }
    if(hash < 0) hash = -hash;
    hash = hash % this->max;
    return hash;
}

void put(Generic *key, Generic *value){
    // if((float)this->size / (float)this->max > 0.88) redimensionar(this->max*this->coef1 + this->coef2);
    int j = hash(key);
    while(this->vetor[j] && this->vetor[j]->key->equals(key)){
        j++;
        if(j == this->max) j=0;
    }
    if(this->vetor[j]) {
        this->vetor[j]->value = value;
    }else{
        this->vetor[j] = (HashTable_Node *) malloc(sizeof(HashTable_Node));
        this->vetor[j]->key = key;
        this->vetor[j]->value = value;
        this->size++;
    }
}

Generic *get(Generic *key){
    int j = hash(key);
    printf("%d\n", j);
    while(this->vetor[j] && key->equals(this->vetor[j]->key) != 0 ){// && (this->vetor[j]->key == 0 || key->equals(this->vetor[j]->key))){
        j++;
        if(j == this->max) j=0;
    }
    if(this->vetor[j]) return this->vetor[j]->value;
    return 0;
}

HashTable *criarHashTable(){
    this = (HashTable *) malloc(sizeof(HashTable));
    this->size = 0;
    this->max = this->min = 10;
    this->coef1 = 1.25;
    this->coef2 = 5;
    this->vetor = (HashTable_Node* *) malloc(sizeof(HashTable_Node *) * this->max);
    for(int i=0; i<this->max; i++) this->vetor[i] = 0;
    this->put = put;
    this->get = get;
    return this;
}