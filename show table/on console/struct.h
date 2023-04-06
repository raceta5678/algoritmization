#ifndef UNTITLED106_STRUCT_H
#define UNTITLED106_STRUCT_H
typedef struct Keyspace{
    unsigned int par;
    unsigned int key;
    char * info;
}Keyspace;

typedef struct Table{
    Keyspace * ks;
    unsigned int msize;
    unsigned int csize;
}Table;

int check(int * che);
Table * create_table();
char *f_readline();
void swap(Keyspace * a, Keyspace * b);
void call_garbage(Table * table);
int search(Table * table, unsigned int key);
Table * add_Items(Table * table, unsigned int key, unsigned int par);
void find(Table * table, unsigned int key);
void delete_elem(Table * table, unsigned int key);
void show(Table * table);
Table * special_delete(Table * table, unsigned int key);
void special_find(Table * table, unsigned int par);
void delete_table(Table * table);
void menu();
#endif
