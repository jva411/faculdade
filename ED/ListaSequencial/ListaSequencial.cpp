#include <new>

using namespace std;

template <typename T> struct ListaSequencial {

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
        if(i<0 || i >= size) throw "IndexOutOfRangeException"; 
        T *temp = vetor[index];
        vetor[index] = vetor[--size];
        if(size < max/4){
            T* *Temp = new(nothrow) No<T>*[max/2];
            if(Temp == nullptr) throw "MemoryOutOfBoundException";
            for(int i=0; i<size; i++) Temp[i] = vetor[i];
            delete vetor[];
            vetor = Temp;
        }
        return temp;
    }

    public: T* get(int index){
        if(i<0 || i >= size) throw "IndexOutOfRangeException"; 
        return vetor[index];
    }

    public: int size(){
        return size;
    }

};