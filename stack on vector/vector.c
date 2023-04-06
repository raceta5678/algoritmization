#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#define STACK_MAX_SIZE 20
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
void push(struct Stack*stack, char* value) {
    if (stack->size >= STACK_MAX_SIZE) {
        free(value);
        DeleteStack(stack);
	printf("\nSorry, Stack OVERFLOW\n");
        exit(STACK_OVERFLOW);
    }
    stack->data[stack->size] = value;
    stack->size++;
}

char * pop(struct Stack *stack) {
    if (stack->size == 0) {
        DeleteStack(stack);
        exit(STACK_UNDERFLOW);
    }
    stack->size--;

    return stack->data[stack->size];
}
void printStack(struct Stack *stack) {
    int i;
    int len = stack->size;
    printf("stack %d : ", stack->size);
    for (i = len - 1; i >=0 ; i--) {
        printf("%s ", stack->data[i]);
    }
    printf("\n");
}

char *f_readline() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

void check(char * data, int * n){
    int len = strlen(data);
    for(int i = 0; i < len; i++){
        if (data[i] <= '0' || data[i] >= '9'){
            (*n)++;
        }
    }
}

struct Stack * input(int *znaki, int *chisla){
    struct Stack * stack = calloc(1, sizeof(struct Stack));
    stack->data = calloc(STACK_MAX_SIZE, sizeof(char *)); // ДОБАВИТЬ ОЧИСТКУ ПАМЯТИ
    stack->size = 0;
    int i = -1;
    int j = 0;
    while (i != 0){
        int n = 0;
        char * t;
        printf("Enter element of stack: ");
        t = f_readline();
        if(t == NULL) {
            i = 0;
        } else {
            check(t, &n);
            if(strcmp(t, "+") == 0 || strcmp(t, "*") == 0 || strcmp(t, "/") == 0 || strcmp(t, "-") == 0) {
                push(stack, t);
                (*znaki)++;
            } else if (n == 0){
                push(stack, t);
                (*chisla)++;
            } else
                free(t);
            j++;
        }
    }
    return stack;
}

void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j){
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}
char* my_itoa(int value, char* buffer, int base){
    if (base < 2 || base > 32) {
        return buffer;
    }
    int n = abs(value);
    int i = 0;
    while (n){
        int r = n % base;
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
        n = n / base;
    }
    if (i == 0) {
        buffer[i++] = '0';
    }
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
    buffer[i] = '\0'; 
    return reverse(buffer, 0, i - 1);
}

int PrefToInf(struct Stack * stack, char *znak){
    int res = 0;
    int a = 0, b = 0;
    char * elem1 = pop(stack);
    if(strcmp(elem1, "+") == 0){
        printf("(");
        a = PrefToInf(stack, "+");
        my_itoa(a, elem1, 10);
    } else if(strcmp(elem1, "*") == 0){
        printf("(");
        a = PrefToInf(stack, "*");
        my_itoa(a, elem1, 10);
    } else if(strcmp(elem1, "-") == 0) {
        printf("(");
        a = PrefToInf(stack, "-");
        my_itoa(a, elem1, 10);
    } else if(strcmp(elem1, "/") == 0) {
        printf("(");
        a = PrefToInf(stack, "/");
        my_itoa(a, elem1, 10);
    } else {
        printf("(");
        printf("%s", elem1);
        a = atoi(elem1);
    }
    printf(" %s ", znak);
    char * elem2 = pop(stack);
    if(strcmp(elem2, "+") == 0){
        b = PrefToInf(stack, "+");
        printf(")");
        my_itoa(b, elem2, 10);
    } else if(strcmp(elem2, "*") == 0){
        b = PrefToInf(stack, "*");
        printf(")");
        my_itoa(b, elem2, 10);
    } else if(strcmp(elem2, "/") == 0){
        b = PrefToInf(stack, "/");
        printf(")");
        my_itoa(b, elem2, 10);
    } else if(strcmp(elem2, "-") == 0){
        b = PrefToInf(stack, "-");
        printf(")");
        my_itoa(b, elem2, 10);
    } else {
        printf("%s", elem2);
        printf(")");
        b = atoi(elem2);
    }
    if(strcmp(znak, "+") == 0)
        res = a + b;
    else if(strcmp(znak, "/") == 0)
        res = a/b;
    else if(strcmp(znak, "-") == 0)
        res = a-b;
    else if(strcmp(znak, "*") == 0)
        res = a*b;
    if(elem1)
        free(elem1);
    free(elem2);
    return res;
}

void DeleteStack(struct Stack * stack){
    char * data;
    while(stack -> size != 0){
        data = pop(stack);
        free(data);
    }
    free(stack->data);
    free(stack);
}
void menu(){
    int chisla = 0, znaki = 0;
    struct Stack * stack;
    stack = input(&znaki, &chisla);
    if(chisla == znaki + 1) {
	printf("\n");
        printStack(stack);
        printf("\n");
        int res = 0;
        char *znak = pop(stack);
        if (strcmp(znak, "*") == 0)
            res = PrefToInf(stack, "*");
        else if (strcmp(znak, "+") == 0)
            res = PrefToInf(stack, "+");
        else if (strcmp(znak, "-") == 0)
            res = PrefToInf(stack, "-");
        else if (strcmp(znak, "/") == 0)
            res = PrefToInf(stack, "/");
        printf(" = %d\n", res);
        free(stack->data);
        free(stack);
        free(znak);
    } else {
        printf("\nIncorrect input\n");
        DeleteStack(stack);
    }
}
