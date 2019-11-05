#include <string.h>

typedef struct Node Node;
typedef struct hashtable HashTable;

struct Node{
    int KeyInt, Prox, hash;
    char* KeyChar;
    void *Value;
};

Node *newNodeInt(int key, void *value, int hash){
    Node *no = (Node*) malloc(sizeof(Node));
    no->KeyInt = key;
    no->KeyChar = 0;
    no->Value = value;
    no->Prox = -1;
    no->hash = hash;
    return no;
}
Node *newNodeStr(char* key, void *value, int hash){
    Node *no = (Node*) malloc(sizeof(Node));
    no->KeyInt = 0;
    no->KeyChar = key;
    no->Value = value;
    no->Prox = -1;
    no->hash = hash;
    return no;
}

struct hashtable{
    Node* *vetor;
    int n, m, min;
};

void redimensionar(HashTable*, int);

HashTable *newHashTable(){
    HashTable *ht = (HashTable*) malloc(sizeof(HashTable));
    ht->min = 10;
    ht->m = ht->min;
    ht->n = 0;
    ht->vetor = (Node**) malloc(sizeof(Node) * ht->m);
    for(int i=0; i < ht->m; i++) ht->vetor[i] = 0;
    return ht;
}

int hashInt(int key, HashTable *ht){
    if(key < 0) key = -key;
    return key % ht->m;
}
int hashStr(char* key, HashTable *ht){
    int i=0, hash=0;
    while(key[i]){
        hash += (key[i]<<5);
        i++;
    }
    return hashInt(hash, ht);
}

void putStr(HashTable *ht, char* key, void *value){
    if((float)ht->n / (float)ht->m > 0.9) redimensionar(ht, ht->m*2);
    int hash = hashStr(key, ht), j = hash, ant = -1, aux = 1;
    while(ht->vetor[j] != 0){
        if(aux) ant = j;
        j = ht->vetor[j]->Prox;
        if(j == -1) {
            j = hashInt(ant+1, ht);
            aux = 0;
        }
    }
    if(ant != -1) ht->vetor[ant]->Prox = j;
    ht->vetor[j] = newNodeStr(key, value, hash);
    ht->n++;
}
void putInt(HashTable *ht, int key, void *value){
    if((float)ht->n / (float)ht->m > 0.9) redimensionar(ht, ht->m*2);
    int hash = hashInt(key, ht), j = hash, ant = -1, aux = 1;
    while(ht->vetor[j] != 0){
        if(aux) ant = j;
        j = ht->vetor[j]->Prox;
        if(j == -1) {
            j = hashInt(ant+1, ht);
            aux = 0;
        }
    }
    if(ant != -1) ht->vetor[ant]->Prox = j;
    ht->vetor[j] = newNodeInt(key, value, hash);
    ht->n++;
}

void *getStr(HashTable *ht, char* key){
    int j = hashStr(key, ht);
    while(j != -1 && ht->vetor[j] != 0 && strcmp(ht->vetor[j]->KeyChar, key)!=0){
        j = ht->vetor[j]->Prox;
    }
    if(j == -1) return 0;
    return ht->vetor[j]->Value;
}
void *getInt(HashTable *ht, int key){
    int j = hashInt(key, ht);
    while(j != -1 && ht->vetor[j] != 0 && ht->vetor[j]->KeyInt != key){
        j = ht->vetor[j]->Prox;
    }
    if(j == -1) return 0;
    return ht->vetor[j]->Value;
}

void redimensionar(HashTable *ht, int newSize){
    HashTable *Ht = newHashTable();
    Ht->m = newSize;
    Ht->vetor = (Node**) malloc(sizeof(Node) * Ht->m);
    for(int i=0; i<ht->m; i++){
        if(ht->vetor[i] != 0){
            if(ht->vetor[i]->KeyChar == 0) putInt(Ht, ht->vetor[i]->KeyInt, ht->vetor[i]->Value);
            else putStr(Ht, ht->vetor[i]->KeyChar, ht->vetor[i]->Value);
        }
    }
    free(ht->vetor);
    ht->vetor = Ht->vetor;
    ht->m = newSize;
    free(Ht);
}