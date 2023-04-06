#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
int check(int * che)
{
    int x;
    int ch = scanf("%d", &x);
    while (ch == 0 || ch == -1 || ch <= 0)
    {
        if(ch == -1)
        {
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


Table * create_table()
{
    unsigned int msize;
    int che = 0;
    Table * table = calloc(1, sizeof(Table));
    printf("Enter size of your table:");
    table -> msize = check(&che);
    if(che == 0)
    {
        table -> csize = 0;
        Keyspace * ks = calloc(table -> msize, sizeof(Keyspace));
        table -> ks = ks;
    } else {
        printf("Sorry, EOF!!!\n");
        free(table);
        exit(-101);
    }
    return table;
}

char *f_readline()
{
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0)
        {
            if (!res)
            {
                return NULL;
            }
        } else if (n > 0)
        {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else
        {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0)
    {
        res[len] = '\0';
    } else
    {
        res = calloc(1, sizeof(char));
    }
    return res;
}

void swap(Keyspace * a, Keyspace * b)
{
    Keyspace c = *a;
    *a = *b;
    *b = c;
}

void call_garbage(Table * table){
    for(int i = 0; i < table->msize; i++)
    {
        if(table->ks[i].par == 0)
        {
            for (int j = i; j < table->msize; j++)
            {
                if(table -> ks[j].par != 0)
                {
                    swap(&table->ks[i], &table->ks[j]);
                    break;
                }
            }
        }
    }
}

int search(Table * table, unsigned int key)
{
    for (int i = 0; i < table -> msize; i++)
    {
        if(table -> ks[i].key == key && table -> ks[i].par != 0)
        {
            return i;
        }
    }
    return -1;
}

Table * add_Items(Table * table, unsigned int key, unsigned int par)
{
    int s;
    int nulls = 0;
    s = search(table, key);
    if(s != -1){
        printf("Sorry, this key exists in table)\n");
        return table;
    } else if(table->csize == table->msize)
    {
        for(int i = 0; i < table->msize; i++)
        {
            if(table->ks[i].par == 0)
            {
                nulls++;
            }
        }
        if(nulls == table->msize)
        {
            free(table->ks[0].info);
            printf("Enter info:\n");
            getchar();
            table->ks[0].info = f_readline();
            if(table->ks[0].info == NULL)
            {
                printf("Sorry, EOF!!!\n");
                delete_table(table);
                exit(-101);
            }
            table->ks[0].key = key;
            table->ks[0].par = par;
            return table;
        }
        int call = 0;
        for(int i = 0; i < table->msize; i++)
        {
            if(table->ks[i].par > 0)
            {
                call++;
            }
        }
        call_garbage(table);
        if(call == table->msize)
        {
            printf("Sorry, table is Overflow\n");
            return table;
        } else {
            for(int i = 0; i < table->msize; i++)
            {
                if(table->ks[i].par == 0)
                {
                    free(table->ks[i].info);
                    printf("Enter info:\n");
                    getchar();
                    table->ks[i].info = f_readline();
                    if(table->ks[i].info == NULL)
                    {
                        printf("Sorry, EOF!!!\n");
                        delete_table(table);
                        exit(-101);
                    }
                    table->ks[i].key = key;
                    table->ks[i].par = par;
                    return table;
                }
            }
        }
    } else{
        printf("Enter info:\n");
        getchar();
        table->ks[table->csize].info = f_readline();
        if(table->ks[table->csize].info == NULL)
        {
            delete_table(table);
            exit(-101);
        }
        table->ks[table->csize].key = key;
        table->ks[table->csize].par = par;
        (table->csize)++;
    }
    return table;
}

void find(Table * table, unsigned int key)
{
    for(int i = 0; i < table->csize; i++)
    {
        if(table->ks[i].par != 0 && table->ks[i].key == key)
        {
            printf("Element is exist:\n");
            printf(" %u | %u | %s \n", table->ks[i].par, table->ks[i].key, table->ks[i].info);
            return;
        }
    }
    printf("Element is not exist\n");
}

void delete_elem(Table * table, unsigned int key)
{
    int s = search(table, key);
    if(s == -1)
    {
        printf("Element is not exist\n");
        return;
    } else
    {
        table->ks[s].par = 0;
    }
}

void show(Table * table)
{
    printf("_____________________________\n");
    printf("par|key| info \n");
    for(int i = 0; i < table -> msize; i++)
    {
        printf("_____________________________\n");
        if(table->ks[i].info != NULL)
        {
            printf(" %u | %u | %s \n", table->ks[i].par, table->ks[i].key, table->ks[i].info);
        } else
        {
            printf("   |   |   \n");
        }
    }
    printf("_____________________________\n");
}

Table * special_delete(Table * table, unsigned int key){
    delete_elem(table, key);
    for(int i = 0; i < table->msize; i++)
    {
        if(table->ks[i].par == key)
        {
            table->ks[i].par = 0;
        }
    }
    return table;
}

void special_find(Table * table, unsigned int par)
{
    printf("_____________________________\n");
    printf("par|key| info \n");
    printf("_____________________________\n");
    for(int i = 0; i < table->msize; i++)
    {
        if(table->ks[i].par == par)
        {
            printf(" %u | %u | %s \n", table->ks[i].par, table->ks[i].key, table->ks[i].info);
            printf("_____________________________\n");
        }
    }
}

void delete_table(Table * table)
{
    for(int i = 0; i < table->csize; i++)
    {
        free(table->ks[i].info);
    }
    free(table->ks);
    free(table);
}

void menu()
{
    int Exit = 1;
    int a;
    int che = 0;
    unsigned int key;
    unsigned int par;
    Table * my_tab = create_table();
    while(Exit)
    {
        printf("0.Exit\n1.Add\n2.Find\n3.Delete\n4.Show\n5.Special Delete\n6.Special Find\n");
        a = check(&che);
        if(che != 0)
        {
            a = 0;
        }
        switch (a)
        {
            case 0:
                delete_table(my_tab);
                exit(-100);
            case 1:
                printf("Enter key:");
                key = check(&che);
                if(che == 0)
                {
                    printf("Enter par:");
                    par = check(&che);
                    if(che == 0) {
                        my_tab = add_Items(my_tab, key, par);
                    } else{
                        printf("Sorry, EOF!!!\n");
                        delete_table(my_tab);
                        exit(-101);
                    }
                } else
                {
                    printf("Sorry, EOF!!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                break;
            case 2:
                printf("Enter key:");
                key = check(&che);
                if(che == 0)
                {
                    find(my_tab, key);
                } else
                {
                    printf("Sorry, EOF!!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                break;
            case 3:
                printf("Enter key:");
                key = check(&che);
                if(che == 0)
                {
                    delete_elem(my_tab, key);
                } else
                {
                    printf("Sorry, EOF!!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                break;
            case 4:
                show(my_tab);
                break;
            case 5:
                printf("Enter key:");
                key = check(&che);
                if(che == 0)
                {
                    special_delete(my_tab, key);
                } else
                {
                    printf("Sorry, EOF!!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                break;
            case 6:
                printf("Enter key:");
                key = check(&che);
                if(che == 0)
                {
                    special_find(my_tab, key);
                } else
                {
                    printf("Sorry, EOF!!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                break;
        }
    }
}

