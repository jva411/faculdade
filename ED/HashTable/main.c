#include <stdlib.h>
#include <stdio.h>
#include "HashTable.c"

int main() {
    HashTable *ht = newHashTable();
    putStr(ht, "a", "fodase1");
    putStr(ht, "b", "fodase2");
    putInt(ht, 0, "asd");
    putInt(ht, 1, "dsa");
    printf("%s\n", (char*)getStr(ht, "b"));
    printf("%s\n", (char*)getStr(ht, "a"));
    printf("%s\n", (char*)getInt(ht, 0));
    printf("%s\n", (char*)getInt(ht, 1));
    return 0;
}