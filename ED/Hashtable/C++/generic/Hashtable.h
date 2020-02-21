#ifndef DEFINED_Hashtable
#define DEFINED_Hashtable

#pragma region Structs

typedef struct Hashtable_Node Hashtable_Node;
typedef struct Hashtable Hashtable;

struct Hashtable_Node{

    void *Key, *Value;

};

struct Hashtable{

    Hashtable_Node* *vetor;
    int n, m;
    void (*set)(Hashtable *, void *, void *);
    void *(*remove)(Hashtable *, void *);
    void *(*get)(Hashtable *, void *);

};

#pragma endregion

Hashtable* newHashtable();

#endif