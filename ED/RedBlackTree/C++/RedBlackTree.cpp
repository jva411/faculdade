#ifndef DEFINED_RedBlackTree
#define DEFINED_RedBlackTree

#include <stdlib.h>
#include <new>

using namespace std;

template <typename V>
class RedBlackTree{

    private:
        class Node{
            public:
                Node *dad = Null, *left = Null, *right = Null;
                bool isBlack = true;
                int key;
                V *value;

                Node(int key, V *value){
                    this->key = key;
                    this->value = value;
                }
        };

        Node *Null = new Node(0, 0), &Raiz = *Null;
        int size = 0;

        Node *getPosition(int key){

            Node *node = Raiz, *dad = Null;
            while(node != Null && node->key != key){
                dad = node;
                if(key < node->key) node = node->left;
                else node = node->right;
            }
            if(node == Null) return dad;
            return node;

        }

        void fixAdd(Node *node){



        }



    public:
        void add(int key, V &value){

            if(Raiz == Null) {
                Raiz = new Node(key, value);
                size = 1;
            }else{
                Node *node = getPosition(key);
                if(key == node->key) node->value = &value;
                else{
                    Node *newNode = new Node(key, value);
                    newNode->dad = node;
                    if(key < node->key) node->left = newNode;
                    else node->right = newNode;
                    size++;
                    fixAdd();
                }
            }

        }

};


#endif