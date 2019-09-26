#include "ListaSequencial.cpp"

template <typename T> struct Pilha : protected ListaSequencial<T> {

    private: int topo;

    public: void init(){
        ListaSequencial<T>::init();
        topo = -1;
    }

    public: void add(T *x){
        ListaSequencial<T>::add(x);
        topo ++;
    }

    public: T* remove(){
        return ListaSequencial<T>::remove(topo--);
    }

    public: int size(){
        return ListaSequencial<T>::size();
    }

};