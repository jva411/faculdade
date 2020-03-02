#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <new>
//#include "RedBlackTree.cpp"

using namespace std;

class teste{
    public:
        int *null = (int *) malloc(sizeof(int)), *ptr = null;
};

int main(){

    teste &t = *new teste();
    *t.null = 5;
    //int **prt = (int **) malloc(sizeof(int *));
    //*ptr = t.ptr;
    int **ptr = &t.ptr;
    int a = 3;
    (*ptr) = &a;
    **ptr = 82;
    printf("%d %d %d %d\n", *t.null, *t.ptr, **ptr, a);
    return 0;

}