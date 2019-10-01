#include "ArvoreBinariaDeBusca.cpp"
#include <iostream>

int main(){
    ArvoreBinariaDeBusca<int> abb;
    abb.init();
    abb.add(4, new int(23));
    abb.print();
    return 0;
}