#include <iostream>
#include <stdlib.h>
#include <new>
#include "Hashtable.cpp"

using namespace std;

int main(){

    Hashtable &ht = *new Hashtable();
    char* str = (char*) malloc(sizeof(char) * 4);
    ht("asd", &ht);
    cout << ht["asd"] << " " << &ht << " " << ht("asd") << " " << ht["asd"] << " " << ht("asd") << "\n";
    return 0;

}