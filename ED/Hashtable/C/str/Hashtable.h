#ifndef DEFINED_Hashtable
#define DEFINED_Hashtable

typedef struct Hashtable_Node{

    char* key;
    void *value;

} Hashtable_Node;

typedef struct Hashtable Hashtable;

struct Hashtable{

    Hashtable_Node* *vetor;
    int n, m;

    void (*set)(Hashtable *, char*, void *);
    void *(*get)(Hashtable *, char*);
    void *(*remove)(Hashtable *, char*);

};

Hashtable *newHashtable();

#endif