#include "ListaSequencial.cpp"

template <typename T> struct Pilha : protected ListaSequencial<T> {

    private: int start, end;

    public: void init(){
        ListaSequencial<T>::init();
        start = -1;
        end = -1;
    }

    public: bool isFull(){
        return end == start-1;
    }

};