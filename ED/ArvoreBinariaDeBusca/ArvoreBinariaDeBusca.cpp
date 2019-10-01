#include <stdlib.h>
#include <new>
#include <iostream>

using namespace std;

template <typename T> class No{
    public: int chave;
    public: T *info;
    public: No<T> *pai, *esq, *dir;
};

template <typename T> class ArvoreBinariaDeBusca {

    private: No<T>* *vetor;
    private: int max, size;

    public: void init(){
        max = 1;
        size = 0;
        vetor = new(nothrow) No<T>*[max];
        if(vetor == 0) throw "MemoryOutOfBoundException";
    }

    private: No<T>* Get(int chave){
        No<T>* p = vetor[0];
        while(p != 0 && p.chave != chave){
            if(chave <= p.chave) p = p.esq;
            else p = p.dir;
        }
        return p;
    }

    public: void add(int chave, T *x){
        if(size == max){
            max *= 2;
            No<T>* *temp = new(nothrow) No<T>*[max];
            if(temp == 0) throw "MemoryOutOfBoundException";
            for(int i=0; i<size; i++) temp[i] = vetor[i];
            delete[] vetor;
            vetor = temp;
        }
        No<T> no = *(new No<T>), *p = vetor[0], **p2;
        no.chave = chave;
        no.info = x;
        if(p == 0) vetor[0] = &no;
        else{
            if((*p).chave > chave) p2 = &(*p).dir;
            else p2 = &(*p).esq;
            while(*p2 != 0){
                p = *p2;
                if((*p).chave > chave) p2 = &(*p).dir;
                else p2 = &(*p).esq;
            }
            *p2 = &no;
            no.pai = p;
            vetor[size] = &no;
        }
        size++;
    }

    public: void print(){
        printEmOrdem(vetor[0]);
        cout << '\n';
    }

    private: void printEmOrdem(No<T> *p){
        if(p != 0){
            printEmOrdem((*p).esq);
            cout << *(*p).info << ' ';
            printEmOrdem((*p).dir);
        }
    }

};