#include "Collection.cpp"

template <typename T> class Pilha : protected Collection<T> {

    public: void init(){
        Collection<T>::init();
    }

    public: void add(T* x){
        Collection<T>::add(x);
    }

    public: T* remove(){
        return Collection<T>::remove(Collection<T>::size - 1);
    }

};