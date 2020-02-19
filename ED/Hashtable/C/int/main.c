#include <stdlib.h>
#include <stdio.h>
#include "Hashtable.h"

int main(){
    
    Hashtable *ht = newHashtable();
    for(int i=0; i<1000; i++) ht->set(ht, i, ht);

    return 0;
}