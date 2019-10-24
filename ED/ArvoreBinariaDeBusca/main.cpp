#include "ArvoreBinariaDeBusca.cpp"
#include <iostream>

int main(){
    ArvoreBinariaDeBusca<int> abb;
    abb.init();
    abb.add(4, new int(1));
    abb.add(5, new int(2));
    abb.add(6, new int(3));
    abb.add(2, new int(4));
    abb.print();
    // abb.rem(4);
    abb.rem(2);
    abb.print();
    return 0;
}