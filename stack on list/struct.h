#ifndef UNTITLED103_STRUCT_H
#define UNTITLED103_STRUCT_H
struct Node{
    char * data;
    struct Node *next;
};
struct Stack{
    struct Node * head;
};
char *f_readline();
void push(struct Stack * stack, char * data);
void check(char * data, int * n);
char * pop(struct Stack * stack);
void printStack(struct Stack * stack);
struct Stack * input(int *znaki, int *chisla);
void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
char* my_itoa(int value, char* buffer, int base);
int PrefToInf(struct Stack * stack, char *znak);
void DeleteStack(struct Stack * stack);
void menu();
#endif
