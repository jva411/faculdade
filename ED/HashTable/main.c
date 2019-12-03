#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
// #include "HashTable.c"
#include "HashTable2.h"

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

//Main para HashTable 2
void func(int a){
    printf("%d\n", a);
}
int main(){
    HashTable *map1 = criarHashTable();//, *map2 = criarHashTable();
    int *a = (int*) malloc(sizeof(int));
    char* str = (char*) malloc(sizeof(char)*5);
    *a = 23;
    str[0] = 'a';
    str[1] = 's';
    str[2] = 'd';
    str[3] = '\0';
    Generic *obj1 = criarGeneric(a, sizeof(int));
    Generic *obj2 = criarGeneric(str, 4*sizeof(char));
    map1->put(obj1, obj2);
    printf("%p\n",  map1->get(obj1));
    return 0;
}