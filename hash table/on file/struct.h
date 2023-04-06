#ifndef UNTITLED106_STRUCT_H
#define UNTITLED106_STRUCT_H
#include <stdio.h>

typedef struct Keyspace{
    unsigned int par;
    unsigned int key;
    int info_len;
}Keyspace;

typedef struct Table{
    Keyspace * ks;
    unsigned int msize;
    unsigned int csize;
}Table;

int check(int * che);
Table * create_table();
void files_copy(char f_name[], char f_help_name[]);
int file_readline(Table * table, char f_name[], char f_help_name[]);
void swap(Keyspace * a, Keyspace * b);
void call_garbage(Table * table);
int search(Table * table, unsigned int key);
void call_garbage_file(Table * table, char file_text[], char file_help_text[]);
void text_add(Table * table, int position, char f_name[], char f_help_name[]);
Table * add_Items(Table * table, unsigned int key, unsigned int par, char f_name[], char f_help_name[]);
void find(Table * table, unsigned int key,  char f_name[]);
void delete_elem(Table * table, unsigned int key);
void show(Table * table, char file_text[]);
Table * special_delete(Table * table, unsigned int key);
void special_find(Table * table, unsigned int par,  char f_name[]);
void delete_table(Table * table);
void menu();
#endif
