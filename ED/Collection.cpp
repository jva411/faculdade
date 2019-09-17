#include <iostream>
#include <stdlib.h>
#include <new>

using namespace std;

template <typename T> struct Collection {

    T* vetor;
    int size, max;

    void init(){
        size = 0;
        max = 1;
        vetor = new(nothrow) T[max];
        if(vetor == nullptr) throw "MemoryOutOfBoundException";
    }

    void add(T x){
        if(size == max){
            T* temp = new(nothrow) T[max*2];
            if(temp == nullptr) throw "MemoryOutOfBoundException";
            for(int i=0; i<size; i++) temp[i] = vetor[i];
            delete[] vetor;
            vetor = temp;
            max *= 2;
        }
        vetor[size++] = x;
    }

    T remove(int index){
        if(index<0 || index>=size) throw "IndexOutOfRangeException";
        size--;
        T *temp = &vetor[index];
        for(int i=index; i<size;) vetor[i] = vetor[++i];
        return *temp;
    }

    void print(){
        cout << '[';
        for(int i=0; i<size; i++){
            if(i == 0) cout << vetor[i];
            else cout << vetor[i] << ", ";
        }
        cout << "]\n";
    }

};

int main(){
    Collection<int> c;
    c.init();
    c.add(5);
    c.add(6);
    c.print();
    return 0;
}