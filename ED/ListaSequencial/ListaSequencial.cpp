#include <stdlib>
#include <new>

template <typename T> struct No {
    int chave;
    T *info;
};

template <typename T> struct ListaSequencial {

    protected: No<T>* *vetor;
    protected: int size, max;

    public: void init(){
        size = 0;
        max = 1;
        vetor = new(nothrow) T*[max];
        if(vetor == nullptr) throw "MemoryOutOfBoundException";
    }

    public: void add(int chave, T* x){
        if(size == max){
            T* *temp = new(nothrow) T*[max*2];
            if(temp == nullptr) throw "MemoryOutOfBoundException";
            for(int i=0; i<size; i++) temp[i] = vetor[i];
            delete[] vetor;
            vetor = temp;
            max *= 2;
        }
        No<T> no = new No<T>;
        no.chave = chave;
        no.info = x;
        vetor[size++] = &no;
    }

    public: T* remove(int chave){
        T* temp = (T*) nullptr;
        for(int i=0; i<size; i++) {
            if((*vetor[i]).chave == chave){
                size--;
                temp = (*vetor[i]).info;
                vetor[i] = vetor[size];
                break;
            }
        }
        if(size < max/4){
            No<T>* *temp = new(nothrow) No<T>*[max/2];
            if(temp == nullptr) throw "MemoryOutOfBoundException";
            for(int i=0; i<size; i++) temp[i] = vetor[i];
            delete vetor[];
            vetor = temp;
        }
        return temp;
    }

    public: T* get(int chave){
        for(int i=0; i<size; i++) if((*vetor[i]).chave == chave) return (*vetor[i]).info;
        return (T*) nullptr;
    }

    public: int size(){
        return size;
    }

};