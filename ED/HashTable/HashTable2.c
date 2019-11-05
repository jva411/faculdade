#include <string.h>

#define COMPARE_VECTORS(v1, v2, size1, size2, i) if(size1!=size2) return 0;for(; i<size1; i++) if(v1[i] != v2[i]) return 0; return 1;

typedef struct Node Node;
typedef struct hashtable HashTable;

struct Node{
    int isVetor, size;
    void *Key, *Value;
};

Node *newNode(void *key, void *value, int keyIsVector, int size){
    Node *no = (Node*) malloc(sizeof(Node));
    no->Key = key;
    no->Value = value;
    no->isVetor = keyIsVector;
    no->size = size;
    return no;
}

struct hashtable{
    Node* *vetor, *rem;
    int n, m, min;
};

HashTable *newHashTable(){
    HashTable *ht = (HashTable*) malloc(sizeof(HashTable));
    ht->min = 10;
    ht->m = ht->min;
    ht->n = 0;
    ht->vetor = (Node**) malloc(sizeof(Node) * ht->m);
    ht->rem = newNode(0, 0);
    for(int i=0; i < ht->m; i++) ht->vetor[i] = 0;
    return ht;
}

void put(HashTable *ht, void *key, void *value, int hash, int keyIsVector, int size){
    while(ht->vetor[hash] != 0 && ht->vetor[hash] != ht->null){
        ++j%ht->m;
    }
    ht->vetor[j] = newNodeStr(key, value, keyIsVector, size);
}

void *get(HashTable *ht, void *key, int hash, int keyIsVector, int size){
    for(int j = hash; j != -1 && ht->vetor[j] != 0; j++){
        if(keyIsVector){
            if(ht->vetor[j]->isVetor){
                if(COMPARE_VECTORS(key, ht->vetor[j]->Key, size, ht->vetor[j]->size)) return ht->vetor[j]->Value;
            }else continue;
        }
        if(ht->vetor[j]->isVetor) continue;
    }
    return 0;
}