#include <stdlib.h>
#include <stdio.h>
#include "Hashtable.h"

int main(){
    
    Hashtable *ht = newHashtable();
    for(int i=0; i<10000000; i++) ht->set(ht, i, ht);

    printf("%p\n", ht->get(ht, 9999999));

    return 0;
}