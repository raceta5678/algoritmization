#ifndef UNTITLED97_STRUCT_H
#define UNTITLED97_STRUCT_H
struct Lines{
    int n;
    int * A;
    struct Lines *next;
};
struct matrix{
    int m;
    struct Lines * start;
    struct Lines * end;
};
int check(int *che);
struct matrix * Create_line(struct matrix * matrix, int n, int * y, int *ch);
void  print(struct matrix * matr);
void swap(struct Lines * a, struct Lines * b);
struct Lines * check_plus(struct matrix * matrix);
struct Lines * check_minus(struct matrix * matrix);
void delete_matrix(struct matrix * matrix);
void menu();
#endif
