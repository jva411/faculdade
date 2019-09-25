#include <iostream>
using namespace std;
#include "ListaSequencial.cpp"

int main(){
    ListaSequencial<int> ls;
    int chaves[1] = {1};
    ls.init();
    ls.add(new int(5), 1);
    for(int i=0; i<1; i++) cout << *ls.get(chaves[i]) << '\n';
    for(int i=0; i<1; i++) cout << *ls.remove(chaves[i]) << '\n';
    return 0;
}