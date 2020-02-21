#include "Hashtable.h"
#include <stdlib.h>

#pragma region Functioncs declaration

void set(Hashtable *, void *, void *);
void *remove(Hashtable *, void *);
void *get(Hashtable *, void *);
unsigned int hash(Hashtable *, void *);
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

Hashtable_Node *newHashtable_Node(void *key, void *value){

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
    for(int i=ht->m-1; i; i--) ht->vetor[i] = 0;
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

void set(Hashtable *this, void *key, void *value){
    
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

void *remove(Hashtable *this, void *key){

    if(Hashtable_RESIZE_CONDITION_2) redimensionar(this, Hashtable_RESIZE_OPERATION_2);
    unsigned int Hash = hash(this, key);
    while(this->vetor[Hash] && ( this->vetor[Hash] == Null || this->vetor[Hash]->Key != key )){
        if(++Hash == this->m) Hash = 0;
    }
    if(this->vetor[Hash]) {
        void *p = this->vetor[Hash]->Value;
        free(this->vetor[Hash]);
        this->vetor[Hash] = Null;
        this->n--;
        return p;
    }
    return 0;

}

void *get(Hashtable *this, void *key){

    unsigned int Hash = hash(this, key);
    while(this->vetor[Hash] && ( this->vetor[Hash] == Null || this->vetor[Hash]->Key != key )){
        if(++Hash == this->m) Hash = 0;
    }
    if(this->vetor[Hash]) return this->vetor[Hash]->Value;
    return 0;

}

unsigned int hash(Hashtable *this, void *key){
    // unsigned int Hash = 0;
    // int *p = (int *) key;
    // for(int i=0; i<sizeof(key)/sizeof(int); i++){
    //     Hash = Hash*8193 + p[i] * 8193;
    // }
    return ((unsigned long int)key * 8193)  % this->m;
}

void redimensionar(Hashtable *this, int unsigned newSize){
    if(newSize < Hashtable_MIN) newSize = Hashtable_MIN;
    Hashtable *Ht = newHashtable();
    Ht->m = newSize;
    Ht->vetor = (Hashtable_Node* *) malloc(sizeof(Hashtable_Node) * Ht->m);
    for(int i=Ht->m-1; i; i--) Ht->vetor[i] = 0;
    for(int i=this->m-1; i; i--){
        if(this->vetor[i]){
            if(this->vetor[i] != Null) set(Ht, this->vetor[i]->Key, this->vetor[i]->Value);
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