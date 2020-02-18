#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// #include <unistd.h>
#include <windows.h>
// #include "int/HashTable.c"
#include "generic/HashTable.h"

#define DELTA_MS(T0, T1) (t1.tv_sec - t0.tv_sec) * 1000 + (t0.tv_nsec - t1.tv_nsec) / 1000000

char *GET(int i){
    char* str = malloc(sizeof(char)*16), j = 0;
    while(i>25){
        str[j] = 'a' + i%26;
        j++;
        i /= 26;
    }
    str[j] = 'a'+i;
    str[j+1] = 0;
    return str;
}

char *getRandom(){
    char* str = (char*) malloc(sizeof(char)*10);
    for(int i=0; i<9; i++){
        if(rand()%2 == 0){
            str[i] = (rand() % 10) + '0';
        }else{
            str[i] = (rand() % 26) + 'A';
        }
    }
    str[9] = 0;
    return str;
}

// Main para HashTable 1
// int main() {
//     srand(time(0));
//     struct timespec t0, t1;
//     HashTable *ht = newHashTable();
//     // for(int i=0; i<10; i++) putInt(ht, i, GET(i));
//     printf("Start\n");
//     clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
//     for(int i=0; i<1000000; i++) putStr(ht, getRandom(), (int*) malloc(sizeof(int)));
//     // for(int i=0; i<500000; i++) putStr(ht, GET(i), (int*) malloc(sizeof(int)));
//     // for(int i=0; i<5000000; i++) putInt(ht, (ht->m * i), GET(i));
//     clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//     printf("End\n");
//     printf("%ld\n", DELTA_MS(t0, t1));
//     return 0;
// }


typedef struct Teste{

    float x, y, raio;
    char* name;

} Teste;


//Main para HashTable 2
int main(){
    HashTable *map1 = newHashTable(), *map2 = newHashTable();
    Generic *obj1 = criarGeneric(5, -1);
    Generic *obj2 = criarGeneric((int)"asd", 4*sizeof(char));
    map1->put(map1, obj1, obj2);
    printf("%p\n", map1->get(map1, obj1));
    printf("%s\n",  (char*) map1->get(map1, obj1)->pointer);
    printf("%s ", (char*)map1->remove(map1, obj1)->pointer);
    printf("%p\n", map1->get(map1, obj1));
    Generic *obj3 = criarGenericFloat(5.0);
    printf("%d\n", obj3->compare(obj3, obj1));

    Teste *t1 = (Teste*) malloc(sizeof(Teste)), *t2 = (Teste*) malloc(sizeof(Teste));
    t1->x = t2->x = 2.5;
    t1->y = t2->y = 2.5;
    t1->raio = 5;
    t2->raio = 3;
    t1->name = "asd";
    t2->name = "asd";
    Generic *T1 = criarGeneric((int)t1, sizeof(t1)), *T2 = criarGeneric((int)t2, sizeof(t2));
    printf("%d %d\n", sizeof(Teste), T1->compare(T1, T2));
    return 0;
}