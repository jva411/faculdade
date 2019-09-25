#include "ListaSequencial.cpp"

temaplate <typename T> struct Pilha : protected ListaSequencial<T> {

    private: int topo;

    public: void init(){
        ListaSequencial::init();
        topo = -1;
    }

    public: void add(T *x){
        ListaSequencial::add(x);
        topo ++;
    }

    public: T* remove(){
        return ListaSequencial::remove(topo--);
    }

    public: int size(){
        return ListaSequencial::size();
    }

}