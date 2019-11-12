#include <string.h>

template <typename K, typename V>
class HashTable {

    private: class Node{
        K *key;
        V *value;
    }

    Node *nodes[];
    int n, min;

    public: void init(){
        n = 0;
        min = 10;
        nodes = new *Node[min];
        for(int i=0; i<min; i++) nodes[i] = 0;
    }
};