#ifndef DEFINED_Hashtable
#define DEFINED_Hashtable

#pragma region Structs

typedef struct Hashtable_Node Hashtable_Node;
typedef struct Hashtable Hashtable;

struct Hashtable_Node{

    int Key;
    void *Value;

};

struct Hashtable{

    Hashtable_Node* *vetor;
    int n, m;
    void (*set)(Hashtable *, unsigned int, void *);
    void *(*remove)(Hashtable *, unsigned int);
    void *(*get)(Hashtable *, unsigned int);

};

#pragma endregion

Hashtable* newHashtable();

#endif