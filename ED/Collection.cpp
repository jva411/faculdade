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
        if(index<0 || index>=size) {
            try{
                T arr[size];
                arr[index];
            }catch(exception& e){
                std::cerr << e.what() << "IndexOutOfRange";
            }
        }
        size--;
        T temp = vetor[index];
        for(int i=index; i<size; i++) vetor[i] = vetor[i + 1];
        return temp;
    }

    void print(){
        cout << '[';
        for(int i=0; i<size; i++){
            if(i == 0) cout << vetor[i];
            else cout << ", " << vetor[i];
        }
        cout << "]\n";
    }

};

int main(){
    Collection<int> c;
    c.init();
    for(int i=0; i<65; i++) c.add(i);
    cout << '[';
    for(int i=0; i<66; i++) cout << c.remove(0) << ", ";
    cout << "]\n";
    return 0;
}