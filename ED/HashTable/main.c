#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "HashTable.c"

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

int main() {
    struct timespec t0, t1;
    HashTable *ht = newHashTable();
    // for(int i=0; i<10; i++) putInt(ht, i, GET(i));
    printf("Start\n");
    clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
    for(int i=0; i<5000000; i++) putInt(ht, i, GET(i));
    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
    printf("End\n");
    printf("%ld\n", DELTA_MS(t0, t1));
    return 0;
}