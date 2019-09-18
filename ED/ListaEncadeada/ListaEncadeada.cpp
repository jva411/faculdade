#include <iostream>
#include <stdlib.h>
#include <new>

using namespace std;

template <typename T> struct No {

    int chave;
    T *info;
    No<T> *ant, *prox;

};

template <typename T> class ListaEncadeda {

    No<T> *primeiro;
    int size;

    public: void init(){
        size = 0;
        primeiro = new No<T>;
        (*primeiro).chave = -1;
        (*primeiro).info = nullptr;
        (*primeiro).prox = primeiro;
        (*primeiro).ant = primeiro;
    }

    public: No<T>* newNo(){
        return (No<T> *) new No<T>;
    }

    public: int add(T *x){
        No<T> *no = new No<T>;
        (*no).info = x;
        (*no).prox = primeiro;
        (*no).ant = (*primeiro).ant;
        (*(*no).ant).prox = no;
        (*primeiro).ant = no;
        (*no).chave = (*(*no).ant).chave+1;
        return (*no).chave;
    }

    public: No<T>* get(int chave){
        No<T> *p = (*primeiro).prox;
        while(p != primeiro && (*p).chave != chave) p = (*p).prox;
        return p;
    }

    public: T* remove(No<T> *no){
        (*(*no).ant).prox = (*no).prox;
        (*(*no).prox).ant = (*no).ant;
        if(no != primeiro){
            (*no).prox = nullptr;
            (*no).ant = nullptr;
            (*no).chave = -1;
        }
        return (*no).info;
    }

    public: T* remove(int chave){
        return remove(get(chave));
    }

};

template <typename T>
void print(ListaEncadeda<T> *LC){
    No<T> *p = (*(*LC).primeiro).prox;
    cout << '[';
    while(p != (*LC).primeiro) {
        if((*p).chave == 0) cout << *(*p).info;
        else cout << ", " << *(*p).info;
        p = (*p).prox;
    }
    cout << "]\n";
}