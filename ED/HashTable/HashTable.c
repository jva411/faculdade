#include <string.h>

typedef struct Node Node;
typedef struct hashtable HashTable;

struct Node{
    int* KeyInt;
    char* KeyChar;
    void *Value;
};

Node *newNodeInt(int key, void *value){
    Node *no = (Node*) malloc(sizeof(Node));
    no->KeyInt = (int*) malloc(sizeof(int));
    *no->KeyInt = key;
    no->KeyChar = 0;
    no->Value = value;
    return no;
}
Node *newNodeStr(char* key, void *value){
    Node *no = (Node*) malloc(sizeof(Node));
    no->KeyInt = 0;
    no->KeyChar = key;
    no->Value = value;
    return no;
}

struct hashtable{
    Node* *vetor, *null;
    int n, m, min;
    float coef1, coef2;
};

void redimensionar(HashTable*, int);

HashTable *newHashTable(){
    HashTable *ht = (HashTable*) malloc(sizeof(HashTable));
    ht->min = 10;
    ht->m = ht->min;
    ht->n = 0;
    ht->vetor = (Node**) malloc(sizeof(Node) * ht->m);
    ht->null = newNodeInt(0, 0);
    ht->coef1 = 1.25;
    ht->coef2 = 5;
    for(int i=0; i < ht->m; i++) ht->vetor[i] = 0;
    return ht;
}

int hashInt(int key, HashTable *ht){
    key *= 8193;
    if(key < 0) key = -key;
    return key % ht->m;
}
int hashStr(char* key, HashTable *ht){
    int i=0, hash=0;
    while(key[i]){
        // hash += (key[i]*8193);
        hash = hash*8193 + key[i]*8193;
        i++;
    }
    if(hash < 0) return (-hash) % ht->m;
    return hash % ht->m;
}

void putStr(HashTable *ht, char* key, void *value){
    if((float)ht->n / (float)ht->m > 0.9) redimensionar(ht, ht->m*ht->coef1 + ht->coef2);
    int j = hashStr(key, ht);
    while(ht->vetor[j] != 0 && strcmp(ht->vetor[j]->KeyChar, key) != 0){
        j++;
        if(j==ht->m) j=0;
    }
    if(ht->vetor[j] != 0) {
        ht->vetor[j]->Value = value;
    }else{
        ht->vetor[j] = newNodeStr(key, value);
        ht->n++;
    }
}
void putInt(HashTable *ht, int key, void *value){
    if((float)ht->n / (float)ht->m > 0.9) redimensionar(ht, ht->m*ht->coef1 + ht->coef2);
    int j = hashInt(key, ht);
    while(ht->vetor[j] != 0 && *ht->vetor[j]->KeyInt != key){
        j++;
        if(j==ht->m) j=0;
    }
    if(ht->vetor[j] != 0) {
        ht->vetor[j]->Value = value;
    }else{
        ht->vetor[j] = newNodeInt(key, value);
        ht->n++;
    }
}

void *getStr(HashTable *ht, char* key){
    int j = hashStr(key, ht);
    while(ht->vetor[j] != 0 && (ht->vetor[j]->KeyChar == 0 || strcmp(key, ht->vetor[j]->KeyChar) != 0)){
        j++;
        if(j == ht->m) j=0;
    }
    if(ht->vetor[j] == 0) return 0;
    return ht->vetor[j]->Value;
}
void *getInt(HashTable *ht, int key){
    int j = hashInt(key, ht);
    while(ht->vetor[j] != 0 && (ht->vetor[j]->KeyInt == 0 || *ht->vetor[j]->KeyInt != key)){
        j++;
        if(j == ht->m) j=0;
    }
    if(ht->vetor[j] == 0) return 0;
    return ht->vetor[j]->Value;
}

void *remStr(HashTable *ht, char* key){
    if(((float)ht->m / (float)ht->n) < 0.7) redimensionar(ht, (ht->m -ht->coef2) / ht->coef1);
    int j = hashStr(key, ht);
    while(ht->vetor[j] != 0 && (ht->vetor[j] == ht->null || strcmp(key, ht->vetor[j]->KeyChar) != 0)){
        j++;
        if(j == ht->m) j=0;
    }
    if(ht->vetor[j] == 0) return 0;
    ht->n--;
    void *p = ht->vetor[j];
    ht->vetor[j] = ht->null;
    return p;
}
void *remInt(HashTable *ht, int key){
    int j = hashInt(key, ht);
    while(ht->vetor[j] != 0 && (ht->vetor[j]->KeyInt == 0 || *ht->vetor[j]->KeyInt != key)){
        j++;
        if(j == ht->m) j=0;
    }
    if(ht->vetor[j] == 0) return 0;
    ht->n--;
    void *p = ht->vetor[j];
    ht->vetor[j] = ht->null;
    return p;
}

void redimensionar(HashTable *ht, int newSize){
    if(newSize < 10) newSize = 10;
    HashTable *Ht = newHashTable();
    Ht->m = newSize;
    Ht->vetor = (Node**) malloc(sizeof(Node) * Ht->m);
    for(int i=0; i<ht->m; i++){
        if(ht->vetor[i] != 0){
            if(ht->vetor[i]->KeyChar == 0) {
                putInt(Ht, *ht->vetor[i]->KeyInt, ht->vetor[i]->Value);
                free(ht->vetor[i]->KeyInt);
            }else {
                putStr(Ht, ht->vetor[i]->KeyChar, ht->vetor[i]->Value);
            }
        }
        free(ht->vetor[i]);
    }
    free(ht->vetor);
    ht->vetor = Ht->vetor;
    ht->m = newSize;
    free(Ht->null);
    free(Ht);
}