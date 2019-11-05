#include <string.h>

typedef struct Node Node;
typedef struct hashtable HashTable;

struct Node{
    int KeyInt, Prox;
    char* KeyChar;
    void *Value;
};

Node *newNodeInt(int key, void *value){
    Node *no = (Node*) malloc(sizeof(Node));
    no->KeyInt = key;
    no->KeyChar = 0;
    no->Value = value;
    no->Prox = -1;
    return no;
}
Node *newNodeStr(char* key, void *value){
    Node *no = (Node*) malloc(sizeof(Node));
    no->KeyInt = 0;
    no->KeyChar = key;
    no->Value = value;
    no->Prox = -1;
    return no;
}

struct hashtable{
    Node* *vetor;
    int n, m, min;
};

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
    int j = hashStr(key, ht), ant = -1, aux = 1;
    while(ht->vetor[j] != 0){
        if(aux) ant = j;
        j = ht->vetor[j]->Prox;
        if(j == -1) {
            j = hashInt(ant+1, ht);
            aux = 0;
        }
    }
    if(ant != -1) ht->vetor[ant]->Prox = j;
    ht->vetor[j] = newNodeStr(key, value);
}
void putInt(HashTable *ht, int key, void *value){
    int j = hashInt(key, ht), ant = -1, aux = 1;
    while(ht->vetor[j] != 0){
        if(aux) ant = j;
        j = ht->vetor[j]->Prox;
        if(j == -1) {
            j = hashInt(ant+1, ht);
            aux = 0;
        }
    }
    if(ant != -1) ht->vetor[ant]->Prox = j;
    ht->vetor[j] = newNodeInt(key, value);
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