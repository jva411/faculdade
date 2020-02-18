#include <stdlib.h>
#include <stdio.h>

#include "Hashtable.h"

int main(){

    Hashtable *ht = newHashtable();
    float f = 4.3;
    int* ia = malloc(5 * sizeof(int));
    for(int i=0; i<5; i++) ia[i++] = i;
    ht->set(ht, ia, 5*sizeof(int), &f);
    printf("%.2f\n", *(float *)ht->get(ht, ia, 5*sizeof(int)));

    char str[] = "oie";
    ht->set(ht, &f, sizeof(float), str);
    f = 4;
    for(int i=0; i<1000; i++){
        f = 4.0 + ((float)i)/1000;
        if(ht->get(ht, &f, sizeof(float))) printf("%f: %s\n", f, (char *) ht->get(ht, &f, sizeof(float)));
   
    }
    return 0;
}