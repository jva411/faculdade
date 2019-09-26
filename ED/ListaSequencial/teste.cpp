#include <iostream>
#include <stdlib.h>

using namespace std;

#include "Pilha.cpp"

struct Base {
    virtual void teste();
    void init(){
        teste();
    }

};

struct Derived : public Base{
    virtual void teste() override{
        cout << "teste\n";
    }
    void init(){
        Base::init();
    }
};

int main(){
    // Pilha<int> P;
    // P.init();
    // for(int i=0; i<5; i++) P.add(new int(i));
    // for(int i=0; i<5; i++) cout << *P.remove() << " ";
    // cout << "\n";
    Derived d;
    d.init();
    return 0;
}