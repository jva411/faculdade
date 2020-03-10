#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <new>
#include "RedBlackTree.cpp"

using namespace std;

int main(){

    RedBlackTree<int> &rbt = *new RedBlackTree<int>();
    int a = 2;
    for(int i=0; i<16; i++) rbt.add(i, a);
    return 0;

}