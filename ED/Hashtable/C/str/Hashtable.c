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
    this->n = 0;
    this->m = Hashtable_MIN;
    if(!Null){
        Null = (Hashtable_Node*) malloc(sizeof(Hashtable_Node));
        Null->key = 0;
        Null->value = 0;
    }
    this->vetor = (Hashtable_Node* *) malloc(sizeof(Hashtable_Node *) * this->m);
    for(int i=0; i<this->m; i++) this->vetor[i] = 0;
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
    return hash % this->m;

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
        if(Hash == this->m) Hash=0;
    }
    if(this->vetor[Hash] && this->vetor[Hash] != Null) {
        this->vetor[Hash]->value = value;
    }else{
        this->vetor[Hash] = (Hashtable_Node *) malloc(sizeof(Hashtable_Node));
        this->vetor[Hash]->key = key;
        this->vetor[Hash]->value = value;
        this->n++;
    }
}

void *get(Hashtable *this, void *key, unsigned int size){
    int Hash = hash(this, key, size);
    while(this->vetor[Hash] == Null || this->vetor[Hash] && !compareKeys(key, size, this->vetor[Hash]->key)){
        Hash++;
        if(Hash == this->m) Hash=0;
    }
    if(this->vetor[Hash]) return this->vetor[Hash]->value;
    return 0;
}

void *remove(Hashtable *this, void *key, unsigned int size){
    if(Hashtable_RESIZE_CONDITION_2) redimensionar(this, Hashtable_RESIZE_OPERATION_2);
    int Hash = hash(this, key, size);
    while(this->vetor[Hash] == Null || (this->vetor[Hash] && !compareKeys(key, size, this->vetor[Hash]->key))){
        Hash++;
        if(Hash == this->m) Hash=0;
    }
    if(this->vetor[Hash]){
        void *value = this->vetor[Hash]->value;
        this->n--;
        free(this->vetor[Hash]);
        this->vetor[Hash] = Null;
        return value;
    }
    return 0;
}

void redimensionar(Hashtable *this, int unsigned newSize){
    if(newSize < Hashtable_MIN) newSize = Hashtable_MIN;
    Hashtable *Ht = newHashtable();
    Ht->m = newSize;
    Ht->vetor = (Hashtable_Node* *) malloc(sizeof(Hashtable_Node) * Ht->m);
    for(int i=Ht->m-1; i; i--) Ht->vetor[i] = 0;
    for(int i=this->m-1; i; i--){
        if(this->vetor[i]){
            if(this->vetor[i] != Null) set(Ht, this->vetor[i]->key, this->vetor[i]->value);
            free(this->vetor[i]);
        }
    }
    free(this->vetor);
    this->vetor = Ht->vetor;
    this->m = newSize;
    free(Ht->get);
    free(Ht->remove);
    free(Ht->set);
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