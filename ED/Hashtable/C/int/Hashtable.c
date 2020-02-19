#include "Hashtable.h"
#include <stdlib.h>

#pragma region Functioncs declaration

void set(Hashtable *, unsigned int, void *);
void *remove(Hashtable *, unsigned int);
void *get(Hashtable *, unsigned int);
unsigned int hash(Hashtable *, unsigned int);
void redimensionar(Hashtable *, unsigned int);

#pragma endregion

#pragma region TEMP_DEFINEDS

#define Hashtable_MIN 10
#define Hashtable_COEFFICIENT_1 1.25
#define Hashtable_COEFFICIENT_2 5
#define Hashtable_RESIZE_CONDITION_1 ((float)this->n / (float)this->m > 0.9)
#define Hashtable_RESIZE_CONDITION_2 (((float)this->m / (float)this->n) < 0.7)
#define Hashtable_RESIZE_OPERATION_1 (this->m * Hashtable_COEFFICIENT_1 + Hashtable_COEFFICIENT_2)
#define Hashtable_RESIZE_OPERATION_2 ((this->m - Hashtable_COEFFICIENT_2) / Hashtable_COEFFICIENT_1)

#pragma endregion

Hashtable_Node *Null = 0;

Hashtable_Node *newHashtable_Node(unsigned int key, void *value){

    Hashtable_Node *htn = (Hashtable_Node *) malloc(sizeof(Hashtable_Node));
    htn->Key = key;
    htn->Value = value;
    return htn;

}

Hashtable *newHashtable(){
    
    Hashtable *ht = (Hashtable *) malloc(sizeof(Hashtable));
    ht->m = Hashtable_MIN;
    ht->n = 0;
    ht->vetor = (Hashtable_Node**) malloc(sizeof(Hashtable_Node) * ht->m);
    for(int i=0; i < ht->m; i++) ht->vetor[i] = 0;
    ht->remove = remove;
    ht->get = get;
    ht->set = set;
    if(!Null) {
        Null = (Hashtable_Node *) malloc(sizeof(Hashtable_Node));
        Null->Key = 0;
        Null->Value = 0;
    }
    return ht;

}

void set(Hashtable *this, unsigned int key, void *value){
    if(value == 0) return remove(this, key);
    if(Hashtable_RESIZE_CONDITION_1) redimensionar(this, Hashtable_RESIZE_OPERATION_1);
    unsigned int Hash = hash(this, key);
    while(this->vetor[Hash] && this->vetor[Hash] != Null && this->vetor[Hash]->Key != key ){
        if(++Hash == this->m) Hash = 0;
    }
    if(!this->vetor[Hash] || this->vetor[Hash] == Null) {
        this->vetor[Hash] = newHashtable_Node(key, value);
        this->n++;
    }else{
        this->vetor[Hash]->Value = value;
    }
}

void *remove(Hashtable *this, unsigned int key){

    if(Hashtable_RESIZE_CONDITION_2) redimensionar(this, Hashtable_RESIZE_OPERATION_2);
    unsigned int Hash = hash(this, key);
    while(this->vetor[Hash] && ( this->vetor[Hash] == Null || this->vetor[Hash]->Key != key )){
        if(++Hash == this->m) Hash = 0;
    }
    if(!this->vetor[Hash]) return 0;
    void *p = this->vetor[Hash]->Value;
    free(this->vetor[Hash]);
    this->vetor[Hash] = 0;
    this->n--;
    return p;

}

void *get(Hashtable *this, unsigned int key){
    unsigned int Hash = hash(this, key);
    while(this->vetor[Hash] && ( this->vetor[Hash] == Null || this->vetor[Hash]->Key != key )){
        if(++Hash == this->m) Hash = 0;
    }
    if(this->vetor[Hash]) return this->vetor[Hash]->Value;
    return 0;
}

unsigned int hash(Hashtable *this, unsigned int key){
    return (key * 8193) % this->m;
}

void redimensionar(Hashtable *this, int unsigned newSize){
    if(newSize < Hashtable_MIN) newSize = Hashtable_MIN;
    Hashtable *Ht = newHashtable();
    Ht->m = newSize;
    Ht->vetor = (Hashtable_Node* *) malloc(sizeof(Hashtable_Node) * Ht->m);
    for(int i=0; i<this->m; i++) Ht->vetor[i] = 0;
    for(int i=0; i<this->m; i++){
        if(this->vetor[i]){
            set(Ht, this->vetor[i]->Key, this->vetor[i]->Value);
            free(this->vetor[i]);
        }
    }
    free(this->vetor);
    this->vetor = Ht->vetor;
    this->m = newSize;
    free(Ht);
}







#pragma region Undefines

#undef Hashtable_MIN
#undef Hashtable_COEFFICIENT_1
#undef Hashtable_COEFFICIENT_2
#undef Hashtable_RESIZE_CONDITION_1
#undef Hashtable_RESIZE_CONDITION_2
#undef Hashtable_RESIZE_OPERATION_1
#undef Hashtable_RESIZE_OPERATION_2

#pragma endregion