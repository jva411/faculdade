#ifndef DEFINED_Hashtable
#define DEFINED_Hashtable

typedef struct Hashtable_Node{

    char* key;
    void *value;
    int keySize;

} Hashtable_Node;

typedef struct Hashtable Hashtable;

struct Hashtable{

    Hashtable_Node* *vetor;
    int size, max, min;
    float coef1, coef2;

    void (*set)(Hashtable *, char*, void *);
    void *(*get)(Hashtable *, char*);
    void *(*remove)(Hashtable *, char*);

};

Hashtable *newHashtable();

#endif