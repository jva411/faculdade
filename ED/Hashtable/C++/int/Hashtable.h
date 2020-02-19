#ifndef DEFINED_Hashtable
#define DEFINED_Hashtable

#pragma region TEMP_DEFINEDS

#define Hashtable_MIN 10
#define Hashtable_COEFFICIENT_1 1.25
#define Hashtable_COEFFICIENT_2 5
#define Hashtable_RESIZE_CONDITION_1 ((float)this->n / (float)this->m > 0.9)
#define Hashtable_RESIZE_CONDITION_2 (((float)this->m / (float)this->n) < 0.7)
#define Hashtable_RESIZE_OPERATION_1 (this->m * Hashtable_COEFFICIENT_1 + Hashtable_COEFFICIENT_2)
#define Hashtable_RESIZE_OPERATION_2 ((this->m - Hashtable_COEFFICIENT_2) / Hashtable_COEFFICIENT_1)

#pragma endregion

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