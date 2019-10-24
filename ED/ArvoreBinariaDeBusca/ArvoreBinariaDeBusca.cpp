#include <stdlib.h>
#include <new>
#include <iostream>

using namespace std;

template <typename T> struct No{
    int chave;
    T *info;
    No<T> *pai, *esq, *dir;
};

template <typename T> struct ArvoreBinariaDeBusca {

    private: void *nullptr;
    private: int size;
    private: No<T> *root;

    public: void init(){
        nullptr = 0;
        size = 0;
        root = (No<T>*) nullptr;
    }

    public: T *get(int chave){
        No<T> *no = Get(chave);
        if(no == nullptr) return nullptr;
        return no->info;
    }

    private: No<T>* Get(int chave){
        No<T>* p = root;
        while(p != nullptr && p->chave != chave){
            if(chave < p->chave) p = p->esq;
            else p = p->dir;
        }
        return p;
    }

    public: void add(int chave, T *x){
        No<T> *no = new No<T>, *p = (No<T>*) nullptr, **q = &root;
        while(*q != nullptr){
            p = *q;
            if(chave < p->chave) q = &p->esq;
            else q = &p->dir;
        }
        no->chave = chave;
        no->info = x;
        no->pai = p;
        *q = no;
        size++;
    }

    public: T* rem(int chave){
        No<T> *no = Get(chave);
        if(no == nullptr) return (T*) nullptr;
        if(no->esq == nullptr) return Rem(no, no->dir);
        else if(no->dir == nullptr) return Rem(no, no->esq);
        else{
            No<T> *y = sucessor(no);
            transplate(y, y->dir);
            y->dir = no->dir;
            y->esq = no->esq;
            y->esq->pai = y;
            y->dir->pai = y;
            return Rem(no, y);
        }
    }

    private: T* Rem(No<T> *p, No<T> *q){
        transplate(p, q);
        T* x = q->info;
        free(q->pai);
        free(q->esq);
        free(q->dir);
        free(q);
        return x;
    }










    private: void transplate(No<T> *p, No<T> *q){
        if(p->pai == nullptr) root = q;
        else if(p == p->pai->esq) p->pai->esq = q;
        else p->pai->dir = q;
        if(q != nullptr) q->pai = p->pai;
    }

    private: void Free(No<T> *Root){
        if(Root != nullptr){
            Free(Root->esq);
            Free(Root->dir);
            free(Root);
        }
    }

    private: No<T> *sucessor(No<T> *no){
        No<T> *p;
        if(no->dir == nullptr){
            p = no->pai;
            while(p != nullptr && no == p->dir) {
                no = p;
                p = p->pai;
            }
            if(p == nullptr) return p;
            return no;
        }
        p = no->dir;
        while(p != nullptr && p->esq != nullptr) p = p->esq;
        return p;
    }

    public: void print(){
        printEmOrdem(root);
        cout << '\n';
    }

    private: void printEmOrdem(No<T> *p){
        if(p != nullptr){
            printEmOrdem(p->esq);
            cout << *p->info << ' ';
            printEmOrdem(p->dir);
        }
    }

};