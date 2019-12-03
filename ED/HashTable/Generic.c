#include "Generic.h"

Generic *this;

// -1 = MenorQue, 0 = igualÀ, 1 = MaiorQue
int equals(Generic *obj){
    if(this->size == obj->size){
        int *p1 = (int *)this->p, *p2 = (int *)obj->p, size = this->size;
        while(size>0){
            if(*p1 != *p2){
                if(*p1 < *p2) return -1;
                return 1;
            }
            size -= sizeof(int);
        }
        return 0;
    }
    if(this->size < obj->size) return -1;
    return 1;
}

Generic *criarGeneric(void *p, int size){
    this = (Generic*) malloc(sizeof(Generic));
    this->p = p;
    this->size = size;
    this->equals = equals;
    return this;
}