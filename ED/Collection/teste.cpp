#include <stdlib.h>
#include <iostream>

using namespace std;

#include "Collection.cpp"

int main(){
    Collection<int> c;
    c.init();
    c.add(new int(5));
    c.add(new int(2));
}