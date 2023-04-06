#ifndef UNTITLED112_STRUCT_H
#define UNTITLED112_STRUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element{
    char * info;
    char * key;
    int release;
    struct Element * next;
}Elem;

typedef struct Keyspace{
    int rel_size;
    Elem  * head;
}Keyspace;

typedef struct Table{
    int msize;
    int csize;
    Keyspace * ks;
}Table;

void menu();
#endif
