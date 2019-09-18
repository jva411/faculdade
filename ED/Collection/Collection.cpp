#include <stdlib.h>
#include <new>

using namespace std;

template <typename T> class Collection {

    protected: T* *vetor;
    protected: int size, max;

    public: void init(){
        size = 0;
        max = 1;
        vetor = new(nothrow) T*[max];
        if(vetor == nullptr) throw "MemoryOutOfBoundException";
    }

    public: void add(T* x){
        if(size == max){
            T* *temp = new(nothrow) T*[max*2];
            if(temp == nullptr) throw "MemoryOutOfBoundException";
            for(int i=0; i<size; i++) temp[i] = vetor[i];
            delete[] vetor;
            vetor = temp;
            max *= 2;
        }
        vetor[size++] = x;
    }

    public: T* remove(int index){
        if(index<0 || index>=size) {
            return new T;
        }
        size--;
        T *temp = vetor[index];
        if(size < max/4){
            T* *temp2 = new(nothrow) T*[max/2];
            if(temp2==nullptr) throw "MemoryOutOfBoundException";
            for(int i=0; i<index; i++) temp2[i] = vetor[i];
            for(int i=index; i<size; i++) temp2[i] = vetor[i+1];
            delete[] vetor;
            vetor = temp2;
            max /= 2;
        }else for(int i=index; i<size; i++) vetor[i] = vetor[i + 1];
        return temp;
    }

    public: T* get(int index){
        if(index<0 || index>=size) {
            return new T;
        }
        return vetor[index];
    }

    public: int size(){
        return size;
    }

};