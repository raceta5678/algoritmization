#ifndef UNTITLED104_STRUCT_H
#define UNTITLED104_STRUCT_H
struct Stack{
    char ** data;
    int size;
};
void push(struct Stack*stack, char* value);
char * pop(struct Stack *stack);
void printStack(struct Stack *stack);
char *f_readline();
void check(char * data, int * n);
struct Stack * input(int *znaki, int *chisla);
void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
char* my_itoa(int value, char* buffer, int base);
int PrefToInf(struct Stack * stack, char *znak);
void DeleteStack(struct Stack * stack);
void menu();
#endif //UNTITLED104_STRUCT_H
