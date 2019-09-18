#include <iostream>
#include <stdlib.h>
#include <new>
#include "Collection.cpp"

using namespace std;

template <typename T> class Pilha : protected Collection<T> {

    public: void init(){
        Collection<T>::init();
    }

    public: void add(T* x){
        Collection<T>::add(x);
    }

    public: T* remove(){
        return Collection<T>::remove(0);
    }

};