#ifndef LAB4A_BTREE_H
#define LAB4A_BTREE_H
#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"
#include <string.h>
struct node{
    int key;
    char * info;
    struct node *right;
    struct node *left;
    int height;
};

//struct node *add_elements(struct node * el);
//struct node *add_elements_from_file(struct node * el, int key, int info);
void postfix(struct node *el);
struct node * add_element(struct node * el, int key, char *  info);
struct node *delete_min(struct node *el);
struct node *balancing(struct node *el);
struct node * search (struct node * el, int key);
void special_search (struct node * el, int key);
struct node * min_el(struct node * el);
struct node * delete(struct node * el, int key);
void delete_tree(struct node *el);
int get_height(struct node *el);

#endif //LAB4A_BTREE_H
