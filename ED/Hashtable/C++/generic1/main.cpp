#include <iostream>
#include <stdlib.h>
#include <new>
#include "Hashtable.cpp"

using namespace std;

class Ponto{
    public:
        float x, y;
        Ponto(float x, float y){
            this->x = x;
            this->y = y;
        }
};

int main(){

    Hashtable &ht = *new Hashtable();
    Ponto &p1 = *new Ponto(0, 0), &p2 = *new Ponto(3, 4);
    ht(&p1, &p2);
    ht(&p2, &p1);
    cout << &p1 << " " << &p2 << " " << ht[&p1] << " " << ht[&p2] << "\n";


    return 0;

}