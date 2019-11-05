#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "HashTable.c"

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
    struct timespec t0={0, 0}, t1={0, 0}, t2={0, 0};
    HashTable *ht = newHashTable();
    // for(int i=0; i<10; i++) putInt(ht, i, GET(i));
    clock_gettime(CLOCK_MONOTONIC, &t0);
    for(int i=0; i<50000000; i++) putInt(ht, i, GET(i));
    clock_gettime(CLOCK_MONOTONIC, &t1);
    sleep(1);
    clock_gettime(CLOCK_MONOTONIC, &t2);
    printf("%lf %lf %lf\n", t0.tv_sec+1.0e-9, t1.tv_sec+1.0e-9, t2.tv_sec+1.0e-9);
    printf("%ld\n", t1.tv_sec - t0.tv_sec);
    printf("%ld\n", t2.tv_sec - t1.tv_sec);
    return 0;
}