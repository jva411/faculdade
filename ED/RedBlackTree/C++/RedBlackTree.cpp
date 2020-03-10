#ifndef DEFINED_RedBlackTree
#define DEFINED_RedBlackTree

#include <stdlib.h>
#include <new>
#include <string>
#include <stdio.h>

using namespace std;

template <typename V>
class RedBlackTree{

    private:
        class Node{
            public:
                Node *dad, *left, *right;
                bool isBlack = false;
                int key;
                V *value;

                Node(Node * Null, int key, V *value){
                    this->key = key;
                    this->value = value;
                    this->dad = Null;
                    this->left = Null;
                    this->right = Null;
                }

                Node(){
                    this->value = 0;
                    this->isBlack = true;
                }
        };

        Node *Null = new Node(), *Raiz = Null;
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

            while(node != Raiz && !node->dad->isBlack){
                if(node->dad == node->dad->dad->left) {
                    Node *tio = node->dad->dad->right;
                    if(tio->isBlack){
                        rightRotation(node->dad->dad);
                        node->dad->isBlack = true;
                        node->dad->right->isBlack = false;
                    }else{
                        node->dad->isBlack = true;
                        tio->dad->isBlack = false;
                        tio->isBlack = true;
                        node = tio->dad;
                    }
                }else{
                    Node *tio = node->dad->dad->left;
                    if(tio->isBlack){
                        printf("%d %d [%d]\n", node->key, node->dad->key, tio->isBlack);
                        leftRotation(node->dad->dad);
                        node->dad->isBlack = true;
                        node->dad->left->isBlack = false;
                        printf("%d %d %d [%d]\n", node->key, node->dad->key, node->dad->left->key, node->dad->left->isBlack);
                    }else{
                        node->dad->isBlack = true;
                        tio->dad->isBlack = false;
                        tio->isBlack = true;
                        node = tio->dad;
                    }
                }
                
                
            }
            Raiz->isBlack = true;

        }

        void leftRotation(Node *node){

            if(node->right != Null){

                Node *x = node->right;
                x->dad = node->dad;
                node->right = x->left;
                if(x->left != Null) x->left->dad = node;
                x->left = node;
                if(node->dad == Null) Raiz = x;
                else{
                    if(node == node->dad->left) node->dad->left = x;
                    else node->dad->right = x;
                }
                node->dad = x;

            }

        }
        void rightRotation(Node *node){

            if(node->left != Null){

                Node *x = node->left;
                x->dad = node->dad;
                node->left = x->right;
                if(x->right != Null) x->right->dad = node;
                x->right = node;
                if(node->dad == Null) Raiz = x;
                else{
                    if(node == node->dad->right) node->dad->right = x;
                    else node->dad->left = x;
                }
                node->dad = x;

            }

        }



    public:

        RedBlackTree(){
            Null->dad = Null;
            Null->left = Null;
            Null->right = Null;
        }

        void add(int key, V &value){

            if(Raiz == Null) {
                Raiz = new Node(Null, key, &value);
                size = 1;
                Raiz->isBlack = true;
            }else{
                Node *node = getPosition(key);
                if(key == node->key) node->value = &value;
                else{
                    if(key == 15) printf("asd %d[%d]\n", node->key, node->isBlack);
                    Node *newNode = new Node(Null, key, &value);
                    newNode->dad = node;
                    if(key < node->key) node->left = newNode;
                    else node->right = newNode;
                    size++;
                    node = newNode;
                }
                fixAdd(node);
            }
        }

};


#endif