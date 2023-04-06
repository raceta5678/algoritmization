#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
int check(int * che) {
    int x;
    int ch = scanf("%d", &x);
    while (ch == 0 || ch == -1) {
        if(ch == -1){
	    *che = 1;
            return 0;
	}
        scanf("%*[^\n]");
        printf("input error...\n");
        printf("please repeat:");
        ch = scanf("%d", &x);
    }
    return x;
}

struct matrix * Create_line(struct matrix * matrix, int n, int * y, int *ch){
    struct Lines * line = calloc(1, sizeof(struct Lines));
    int * A = calloc(n, sizeof(int));
    line -> A = A;
    line -> n = n;
    for(int i = 0; i < n; i++){
        printf("Enter your %d element:", i+1);
        A[i] = check(ch);
        if (*ch == 1){
//	    delete_matrix(matrix);
            *y = 2;
            return matrix;
        }
    }
    if(!matrix -> start){
        matrix -> start = line;
        matrix -> end = line;
        line -> next = NULL;
    } else{
        struct Lines * line1 = matrix -> end;
        line1 -> next = line;
        matrix -> end = line;
        line -> next = NULL;
    }
    return matrix;
}
void  print(struct matrix * matr){
    struct Lines * line = matr -> start;
    int * A;
    for(int i = 0; i < matr -> m; i ++){
        A = line -> A;
        for(int j = 0; j < line -> n; j++){
            printf("%d ", A[j]);
        }
        printf("\n");
        line = line -> next;
    }
}
void swap(struct Lines * a, struct Lines * b){
    int m = a -> n;
    int * tmp;
    tmp = a -> A;
    a -> A = b -> A;
    a -> n = b -> n;
    b -> A = tmp;
    b -> n = m;
}
struct Lines * check_plus(struct matrix * matrix){
    struct Lines * line = matrix -> start;
    int m = matrix -> m;
    int n;
    int plus = 0;
    int plus1 = 0;
    struct Lines * line_max;
    int * A;
    for(int i = 0; i < m; i++){
        n = line -> n;
        A = line -> A;
        for(int j = 0; j < n; j++){
            if(A[j] >= 0)
                plus1++;
        }
        if(plus1 > plus) {
            plus = plus1;
            line_max = line;
        }
        plus1 = 0;
        line = line -> next;
    }
    if(plus != 0)
        return line_max;
    else
        return matrix -> start;
}
struct Lines * check_minus(struct matrix * matrix){
    struct Lines * line = matrix -> start;
    int m = matrix -> m;
    int n;
    int minus = 0;
    int minus1 = 0;
    struct Lines * line_max;
    int * A;
    for(int i = 0; i < m; i++){
        n = line -> n;
        A = line -> A;
        for(int j = 0; j < n; j++){
            if(A[j] < 0)
                minus1++;
        }
        if(minus1 > minus) {
            minus = minus1;
            line_max = line;
        }
        minus1 = 0;
        line = line -> next;
    }
    if(minus != 0)
        return line_max;
    else
        return matrix -> end;
}
void delete_matrix(struct matrix * matrix){
    struct Lines * ptr = matrix -> start, * ptr_prev;
    while (ptr){
        ptr_prev = ptr;
        ptr = ptr -> next;
        free(ptr_prev -> A);
        free(ptr_prev);
    }
    free(matrix);
}
void menu(){
    int m;
    int n;
    int ch = 0;
    int y = 0;
    struct matrix * Matr = calloc(1, sizeof(struct matrix));
    printf("Enter quantity of your Lines\n");
    m = check(&ch);
    if(m <= 0 && ch != 1){
        while (m <= 0){
            if(ch == 1){
                break;
            }
            printf("Incorrect input...\n");
            printf("please, repeate:");
            m = check(&ch);
        }
    }
    if (ch != 1) {
        Matr->m = m;
        for (int i = 0; i < m; i++) {
            printf("Enter size of your Line:\n");
            n = check(&ch);
            if(n <= 0 && ch != 1){
                while (n <= 0){
                    if(ch == 1){
                        break;
                    }
                    printf("Incorrect input...\n");
                    printf("please, repeate:");
                    n = check(&ch);
                }
            }
            if (ch == 1) {
                break;
            }
            Matr = Create_line(Matr, n, &y, &ch);
            if(y == 2){
                ch = 1;
            }
        }
        if (ch != 1) {
            printf("**Start matrix**\n");
            print(Matr);
            struct Lines *a = Matr->start;
            struct Lines *b = check_plus(Matr);
            swap(a, b);
            struct Lines *c = Matr->end;
            struct Lines *d = check_minus(Matr);
            swap(c, d);
            printf("**End matrix**\n");
            print(Matr);
        }
        delete_matrix(Matr);
//}
    } else
        free(Matr);
}
