#ifndef LAB4A_BTREE_H
#define LAB4A_BTREE_H
#include <stdio.h>
#include <stdlib.h>
struct node{
    int key;
    int info;
    struct node *right;
    struct node *left;
    struct node *root;
};

struct node *add_elements(struct node * el);
struct node *add_elements_from_file(struct node * el, int key, int info);
int get_int(int *a);
void add_element(struct node * el, struct node * el_new);
void postfix(struct node *el);
struct node * search (struct node * el, int key);
struct node * help_search(struct node * el, int key);
void special_search (struct node * el, int key);
struct node * min_el(struct node * el);
void root_changes(struct node * el, struct node * root);
struct node * delete(struct node * el, int key);
void help_delete(struct node * el, struct node * a);
void delete_tree(struct node *el);

#endif //LAB4A_BTREE_H
