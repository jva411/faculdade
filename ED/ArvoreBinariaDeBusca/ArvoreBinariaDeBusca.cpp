#include <new>
#include <cstdlib>
using namespace std;

template <typename T> struct No{
    int chave;
    T *info;
    No<T> *pai, *esq, *dir;
}

template <typename T> struct ArvoreBinariaDeBusca {

    private: No<T>* *vetor;
    private: int max, size;

    void init{
        max = 1;
        size = 0;
        vetor = new(nothrow) No<T>*[max];
        if(vetor == nullptr){
            cout << "MemoryOutOfBoundException";
            exit(1);
        }
    }

    private: No<T>* Get(int chave){
        No<T>* p = vetor[0];
        while(p != nullptr && p.chave != chave){
            if(chave <= p.chave) p = p.esq;
            else p = p.dir;
        }
        return p;
    }

    void add(int chave, T *x){
        if(size == max){
            max *= 2;
            No<T>* *temp = new(nothrow) new No<T>*[max];
            if(temp == nullptr){
                cout << "MemoryOutOfBoundException";
                exit(1);
            }
            for(int i=0; i<size; i++) temp[i] = vetor[i];
            delete[] vetor;
            vetor = temp;
        }
        No<T> no = *(new No<T>), *p = vetor[0], p2**;
        no.chave = chave;
        no.info = x;
        if(p == nullptr) vetor[0] = &no;
        else{
            if(p.chave > chave) p2 = &p.dir;
            else p2 = &p.esq;
            while(*p2 != nullptr){
                p = *p2;
                if(p.chave > chave) p2 = &p.dir;
                else p2 = &p.esq;
            }
            *p2 = &no;
            no.pai = p;
            vetor[size] = &no;
        }
        size++;
    }

}