#include "Hashtable.h"

#pragma region functions declaration

void set(Hashtable *, char*, void *);
void *get(Hashtable *, char*);
void *remove(Hashtable *, char*);
void redimensionar(Hashtable *, int);

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


Hashtable *newHashtable(){

    Hashtable *this = (Hashtable *) malloc(sizeof(Hashtable));
    this->size = 0;
    this->m = Hashtable_MIN;
    if(!Null){
        Null = (Hashtable_Node*) malloc(sizeof(Hashtable_Node));
        Null->key = 0;
        Null->value = 0;
    }
    this->vetor = (Hashtable_Node* *) malloc(sizeof(Hashtable_Node *) * this->max);
    for(int i=0; i<this->max; i++) this->vetor[i] = 0;
    this->set = set;
    this->get = get;
    this->remove = remove;
    return this;

}




unsigned int hash(Hashtable *this, char *key){

    unsigned int hash = 0;
    for(int i=0; key[i]; i++){
        hash = hash*8193 + key[i]*8193;
    }
    return hash % this->max;

}

int compareKeys(char* key1, char*key2){
    
    int i=0;
    do{
        if(key1[i] != key2[i]) return 0;
        i++;
    }while(key1[i]);
    return 1;

}

void set(Hashtable *this, char* key, void *value){
    if(Hashtable_RESIZE_CONDITION_1) redimensionar(this, Hashtable_RESIZE_OPERATION_1);
    int Hash = hash(this, key);
    while(this->vetor[Hash] && this->vetor[Hash] != Null && !compareKeys(key, this->vetor[Hash]->key)){
        Hash++;
        if(Hash == this->max) Hash=0;
    }
    if(this->vetor[Hash] && this->vetor[Hash] != Null) {
        this->vetor[Hash]->value = value;
    }else{
        this->vetor[Hash] = (Hashtable_Node *) malloc(sizeof(Hashtable_Node));
        this->vetor[Hash]->key = key;
        this->vetor[Hash]->value = value;
        this->size++;
    }
}

void *get(Hashtable *this, void *key, unsigned int size){
    int Hash = hash(this, key, size);
    while(this->vetor[Hash] == Null || this->vetor[Hash] && !compareKeys(key, size, this->vetor[Hash]->key, this->vetor[Hash]->keySize)){
        Hash++;
        if(Hash == this->max) Hash=0;
    }
    if(this->vetor[Hash]) return this->vetor[Hash]->value;
    return 0;
}

void *remove(Hashtable *this, void *key, unsigned int size){
    if(Hashtable_RESIZE_CONDITION_2) redimensionar(this, Hashtable_RESIZE_OPERATION_2);
    int Hash = hash(this, key, size);
    while(this->vetor[Hash] == Null || (this->vetor[Hash] && !compareKeys(key, size, this->vetor[Hash]->key, this->vetor[Hash]->keySize))){
        Hash++;
        if(Hash == this->max) Hash=0;
    }
    if(this->vetor[Hash]){
        void *value = this->vetor[Hash]->value;
        this->size--;
        free(this->vetor[Hash]);
        this->vetor[Hash] = Null;
        return value;
    }
    return 0;
}

void redimensionar(Hashtable *this, int newSize){
    if(newSize < this->min) newSize = this->min;
    Hashtable *Ht = newHashtable();
    Ht->max = newSize;
    Ht->vetor = (Hashtable_Node* *) malloc(sizeof(Hashtable_Node) * Ht->max);
    for(int i=0; i<this->max; i++) Ht->vetor[i] = 0;
    for(int i=0; i<this->max; i++){
        if(this->vetor[i] != 0){
            this->set(this, this->vetor[i]->key, this->vetor[i]->keySize, this->vetor[i]->value);
        }
        free(this->vetor[i]);
    }
    free(this->vetor);
    this->vetor = Ht->vetor;
    this->max = newSize;
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