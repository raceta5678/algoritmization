#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void push(struct Stack * stack, char * data){
    struct Node * elem = calloc(1, sizeof(struct Node));
    if(elem == NULL){
        return;
    }
    elem -> data = data;
    if(!stack->head)
        stack -> head = elem;
    else {
        elem->next = stack->head;
        stack->head = elem;
    }

}
void check(char * data, int * n){
    int len = strlen(data);
    for(int i = 0; i < len; i++){
        if (data[i] <= '0' || data[i] >= '9'){
            (*n)++;
        }
    }
}
char * pop(struct Stack * stack){
    struct Node * elem;
    char * data;
    if((stack -> head) == NULL){
        return NULL;
    }
    elem = stack -> head;
    data = elem -> data;
    stack -> head = stack -> head -> next;
    free(elem);
    return data;
}
void printStack(struct Stack * stack){
    printf("\nstack:");

    if(!stack -> head){
        return;
    }

    struct Node * elem = stack -> head;
    while (elem != NULL){
        printf("%s ", elem -> data);
        elem = elem -> next;
    }
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
struct Stack * input(int *znaki, int *chisla){
    struct Stack * stack = calloc(1, sizeof(struct Stack));
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

    if(elem2)
        free(elem2);

    return res;
}

void DeleteStack(struct Stack * stack){
    struct Node * prev = stack -> head;
    struct Node * ptr = prev -> next;
    char * data;
    while(prev != NULL){
        data = pop(stack);
        free(data);
        prev = ptr;
        if(ptr)
            ptr = ptr -> next;
    }
    free(stack);
}
void menu(){
    int chisla = 0, znaki = 0;
    struct Stack * stack;
    stack = input(&znaki, &chisla);
    if(chisla == znaki + 1) {
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
        free(stack);
        free(znak);
    } else {
        printf("\nIncorrect input\n");
        DeleteStack(stack);
    }
}
