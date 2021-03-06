#ifndef DEFINED_Hashtable
#define DEFINED_Hashtable

#include <stdlib.h>
#include <new>

using namespace std;

#pragma region TEMP_DEFINEDS

#define Hashtable_MIN 10
#define Hashtable_COEFFICIENT_1 1.25
#define Hashtable_COEFFICIENT_2 5
#define Hashtable_RESIZE_CONDITION_1 ((float)this->n / (float)this->m > 0.9)
#define Hashtable_RESIZE_CONDITION_2 (((float)this->m / (float)this->n) < 0.7)
#define Hashtable_RESIZE_OPERATION_1 (this->m * Hashtable_COEFFICIENT_1 + Hashtable_COEFFICIENT_2)
#define Hashtable_RESIZE_OPERATION_2 ((this->m - Hashtable_COEFFICIENT_2) / Hashtable_COEFFICIENT_1)

#pragma endregion

template <typename K, typename V>
class Hashtable{

    private:
        class Node{
            
            public:
                K *key;
                V *value;

                Node(K *key, V *value){
                    this->key = key;
                    this->value = value;
                }
        };

        Node* *vetor, *Null;
        int n, m;

        void set(K *key, V *value){
            
            if(Hashtable_RESIZE_CONDITION_1) redimensionar(Hashtable_RESIZE_OPERATION_1);
            unsigned int Hash = hash(key);
            while(this->vetor[Hash] && this->vetor[Hash] != Null && this->vetor[Hash]->key != key ){
                if(++Hash == this->m) Hash = 0;
            }
            if(!this->vetor[Hash] || this->vetor[Hash] == Null) {
                this->vetor[Hash] = new Node(key, value);
                this->n++;
            }else{
                this->vetor[Hash]->value = value;
            }
            
        }

        unsigned int hash(K &key){
            return ((( unsigned long int ) &key) * 8193) % this->m;
        }

        void redimensionar(int unsigned newSize){
            if(newSize < Hashtable_MIN) newSize = Hashtable_MIN;
            Hashtable *Ht = new Hashtable();
            Ht->m = newSize;
            Ht->vetor = (Node* *) malloc(sizeof(Node) * Ht->m);
            for(int i=Ht->m-1; i; i--) Ht->vetor[i] = 0;
            for(int i=this->m-1; i; i--){
                if(this->vetor[i] && this->vetor[i] != Null){
                    Ht->set(this->vetor[i]->key, this->vetor[i]->value);
                    free(this->vetor[i]);
                }
            }
            free(this->vetor);
            this->vetor = Ht->vetor;
            this->m = newSize;
            free(Ht);
        }
    
    public:
        Hashtable(){

            this->m = Hashtable_MIN;
            this->n = 0;
            this->vetor = (Node* *) malloc(sizeof(Node *) * Hashtable_MIN);
            for(int i=Hashtable_MIN-1; i; i--) this->vetor[i] = 0;

        }

        void set(K &key, V &value){
            
            if(Hashtable_RESIZE_CONDITION_1) redimensionar(Hashtable_RESIZE_OPERATION_1);
            unsigned int Hash = hash(key);
            while(this->vetor[Hash] && this->vetor[Hash] != Null && this->vetor[Hash]->key != &key ){
                if(++Hash == this->m) Hash = 0;
            }
            if(!this->vetor[Hash] || this->vetor[Hash] == Null) {
                this->vetor[Hash] = new Node(&key, &value);
                this->n++;
            }else{
                this->vetor[Hash]->value = &value;
            }
            
        }

        V *remove(K &key){

            if(Hashtable_RESIZE_CONDITION_2) redimensionar(Hashtable_RESIZE_OPERATION_2);
            unsigned int Hash = hash(key);
            while(this->vetor[Hash] && ( this->vetor[Hash] == Null || this->vetor[Hash]->key != &key )){
                if(++Hash == this->m) Hash = 0;
            }
            if(this->vetor[Hash]) {
                V *p = this->vetor[Hash]->value;
                free(this->vetor[Hash]);
                this->vetor[Hash] = Null;
                this->n--;
                return p;
            }
            return 0;

        }

        V *get(K &key){
            unsigned int Hash = hash(key);
            while(this->vetor[Hash] && ( this->vetor[Hash] == Null || this->vetor[Hash]->key != &key )){
                if(++Hash == this->m) Hash = 0;
            }
            if(this->vetor[Hash]) return this->vetor[Hash]->value;
            return 0;
        }

        int getSize(){
            return this->n;
        }

        /*
         * get function
         */
        void *operator[](K &key){
            return get(key);
        }
        /*
         * set function
         */
        void operator()(K &key, V &value){
            set(key, value);
        }
        /*
         * remove function
         */
        void *operator()(K &key){
            return remove(key);
        }

};






#pragma region Undefines

#undef Hashtable_MIN
#undef Hashtable_COEFFICIENT_1
#undef Hashtable_COEFFICIENT_2
#undef Hashtable_RESIZE_CONDITION_1
#undef Hashtable_RESIZE_CONDITION_2
#undef Hashtable_RESIZE_OPERATION_1
#undef Hashtable_RESIZE_OPERATION_2

#pragma endregion

#endif