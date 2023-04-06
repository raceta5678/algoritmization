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

Table* create_table()
{
    unsigned int msize;
    int che = 0;
    Table * table = calloc(1, sizeof(Table));
    if (table == NULL)
    {
    	exit(-101);
    }
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

void call_garbage_file(Table * table, char file_text[], char file_help_text[])
{
    FILE * f, *f_help;
    int len = 0;
    int pos = 0;
    char symbol = '\0';
    f = fopen(file_text, "r");
    f_help = fopen(file_help_text, "w");
    for(int i = 0; i < table -> msize; i++)
    {
	    //Проверки на ks
        if(table->ks[i].par > 0)
        {
            while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n')
            {
                fwrite(&symbol, sizeof(char), 1, f_help);
                len++;
              //  printf("<%c> - (%d)\n",symbol, len);
            }
            table->ks[pos].info_len = len;
            len = 0;
            pos++;
//            fread(&symbol, sizeof(char), 1, f);
            fwrite("\n", sizeof(char), 1, f_help);
        } else {
            while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n')
            {
               // continue;
            }
//            fread(&symbol, sizeof(char), 1, f);
        }
    }
    fclose(f);
    f = fopen(file_text, "r");
    len = 0;
    for(int i = 0; i < table -> msize; i++)
    {
        //printf("HEH");
        if(table->ks[i].par == 0)
        {
            while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n')
            {
                fwrite(&symbol, sizeof(char), 1, f_help);
                len++;
            }
            table->ks[pos].info_len = len;
            len = 0;
            pos++;
//            fread(&symbol, sizeof(char), 1, f);
            fwrite("\n", sizeof(char), 1, f_help);
        } else {
            while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n')
            {
                //continue;
            }
//            fread(&symbol, sizeof(char), 1, f);
        }
    }
    fclose(f_help);
    fclose(f);
    files_copy(file_text, file_help_text);
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

int file_readline(Table * table, char f_name[], char f_help_name[])
{
    char symbol = '\0';
    int count = 0;
    FILE *f, *f_help;
    f_help = fopen(f_help_name, "w");
    f = fopen(f_name, "r");

    while(fread(&symbol, 1, 1, f) && symbol!= EOF) {
        fwrite(&symbol, sizeof(char), 1, f_help);
    }
    getchar();
    while((symbol = getchar()) != '\n'){
        if(symbol == EOF){
            printf("Sorry, EOF!!!\n");
            fclose(f);
            f = fopen(f_name, "w");
            fclose(f);
            fclose(f_help);
            f_help = fopen(f_help_name, "w");
            fclose(f_help);
            delete_table(table);
            exit(-101);
        }
        fwrite(&symbol, sizeof(char), 1, f_help);
        count++;
    }
    fwrite("\n", sizeof(char), 1, f_help);
    fclose(f);
    fclose(f_help);
    return count;
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

void text_add(Table * table, int position, char f_name[], char f_help_name[])
{
    FILE * f, *f_help;
    int len = 0;
    char symbol = '\0';
    f = fopen(f_name, "r");
    f_help = fopen(f_help_name, "w");
    for(int i = 0; i < table->msize; i++)
    {
        if(i == position){
            getchar();
            while((symbol = getchar()) != '\n')
            {
                if(symbol == EOF){
                    printf("Sorry, EOF!!!\n");
                    fclose(f);
                    f = fopen(f_name, "w");
                    fclose(f);
                    fclose(f_help);
                    f_help = fopen(f_help_name, "w");
                    fclose(f_help);
                    delete_table(table);
                    exit(-101);
                }
                len++;
                fwrite(&symbol, sizeof(char), 1, f_help);
            }
            fwrite(&symbol, sizeof(char), 1, f_help);
            for(int j = 0; j < table->ks[i].info_len + 1; j++)
            {
                fread(&symbol, sizeof(char), 1, f);
            }
            table->ks[i].info_len = len;
        } else {
            while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n')
            {
                fwrite(&symbol, sizeof(char), 1, f_help);
            }
            fwrite(&symbol, sizeof(char), 1, f_help);
        }
    }
    fclose(f);
    fclose(f_help);
    files_copy(f_name, f_help_name);
}

Table * add_Items(Table * table, unsigned int key, unsigned int par, char f_name[], char f_help_name[])
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
            printf("Enter info:\n");
            text_add(table, 0, f_name, f_help_name);
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
        if(call == table->msize)
        {
            printf("Sorry, table is Overflow\n");
            return table;
        } else {
            call_garbage(table);
            call_garbage_file(table, f_name, f_help_name);
//            show(table, f_name);
//            for (int i = 0; i < table -> msize; i++){
//                printf("\nMOElen %d = %d\n", i, table -> ks[i].info_len);
//            }

            for(int i = 0; i < table->msize; i++)
            {
                if(table->ks[i].par == 0)
                {
                    printf("Enter info:\n");
                    text_add(table, i, f_name, f_help_name);
                    table->ks[i].key = key;
                    table->ks[i].par = par;
                    return table;
                }
            }
        }
    } else{
        printf("Enter info:\n");
        table->ks[table->csize].info_len = file_readline(table, f_name, f_help_name);
        table->ks[table->csize].key = key;
        table->ks[table->csize].par = par;
        (table->csize)++;
    }
    return table;
}

void find(Table * table, unsigned int key, char f_name[])
{
    FILE * f;
    char symbol;
    f = fopen(f_name, "r");
    for(int i = 0; i < table->csize; i++)
    {
        if(table->ks[i].par != 0 && table->ks[i].key == key)
        {
            printf("Element is exist:\n");
            printf(" %u | %u | ", table->ks[i].par, table->ks[i].key);
            while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n'){
                printf("%c", symbol);
            }
            printf("\n");
            fclose(f);
            return;
        }
        for(int j = 0; j < table->ks[i].info_len + 1; j++)
        {
            fread(&symbol, sizeof(char), 1, f);
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

void first_special_function(Table * table, char file_text[], int *position)
{
    FILE *f;
    char symbol = '\0';
    f = fopen(file_text, "r");
    printf("_____________________________\n");
    printf("par|key| info \n");
    for(int i = 0; i < table -> msize; i++)
    {
        if(i == *position){
            printf("_____________________________\n");
            if(table->ks[i].info_len != 0)
            {
                printf(" %u | %u | ", table->ks[i].par, table->ks[i].key);
                while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n'){
                    printf("%c", symbol);
                }
                printf("%c", symbol);
            } else{
                printf("   |   |   \n");
            }
        } else {
            for(int j = 0; j < table->ks[i].info_len + 1; j++)
            {
                fread(&symbol, sizeof(char), 1, f);
            }
        }
    }

    if(*position == table -> msize-1)
    {
        printf("End of iterator\n";

	return;
    }

    (*position)++;
    fclose(f);
}

void show(Table * table, char file_text[])
{
    FILE * f;
    char symbol = '\0';
    f = fopen(file_text, "r");
    printf("_____________________________\n");
    printf("par|key| info \n");
    for(int i = 0; i < table -> msize; i++)
    {

        printf("_____________________________\n");
        if(table->ks[i].info_len != 0)
        {
            printf(" %u | %u | ", table->ks[i].par, table->ks[i].key);
            while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n'){
                printf("%c", symbol);
            }
            printf("%c", symbol);
        } else{
            printf("   |   |   \n");
        }
    }
    printf("_____________________________\n");
    fclose(f);
}

void save_table(Table * table, char file_text[])
{
    FILE * f, * r;
    char otstup[] = "_____________________________";
    char opt[] = " par|key| info ";
    char uchet[] = "   |   |   ";
    char res[] = "result.txt";
    char symbol = '\0';
    f = fopen(file_text, "r");
    r = fopen(res, "w");
    fwrite(otstup, sizeof(char), strlen(otstup), r);
    fwrite("\n", sizeof(char), 1, r);
    fwrite(opt, sizeof(char), strlen(opt), r);
    fwrite("\n", sizeof(char), 1, r);
    for(int i = 0; i < table -> msize; i++)
    {
        fwrite(otstup, sizeof(char), strlen(opt), r);
        fwrite("\n", sizeof(char), 1, r);
        if(table->ks[i].info_len != 0)
        {
            fwrite(" ", sizeof(char), 1, r);
            fwrite(&(table->ks[i].key), sizeof(int), 1, r);
            fwrite(" | ", sizeof(char), 1, r);
            fwrite(&(table->ks[i].par), sizeof(int), 1, r);
            fwrite(" | ", sizeof(char), 1, r);
            for(int j = 0; j < table->ks[i].info_len + 1; j++)
            {
                fread(&symbol, 1, 1, f);
                fwrite(&symbol, sizeof(char), 1, r);
            }
        } else {
            fwrite(uchet, sizeof(char), strlen(uchet), r);
            fwrite("\n", sizeof(char), 1, r);
        }
    }
    fclose(f);
    fclose(r);
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

void special_find(Table * table, unsigned int par, char f_name[])
{
    FILE * f;
    char symbol;
    f = fopen(f_name, "r");
    printf("_____________________________\n");
    printf("par|key| info \n");
    printf("_____________________________\n");
    for(int i = 0; i < table->msize; i++)
    {
        if(table->ks[i].par == par)
        {
            printf(" %u | %u |", table->ks[i].par, table->ks[i].key);
            while (fread(&symbol, sizeof(char), 1, f) && symbol != '\n'){
                printf("%c", symbol);
            }
            printf("\n");
            printf("_____________________________\n");
        } else {
            for(int j = 0; j < table->ks[i].info_len + 1; j++)
            {
                fread(&symbol, sizeof(char), 1, f);
            }
        }
    }
    fclose(f);
}

void delete_table(Table * table)
{
    free(table->ks);
    free(table);
}

void files_copy(char f_name[], char f_help_name[])
{
    char symbol;
    FILE *f, *f_help;
    f = fopen(f_name, "w");
    f_help = fopen(f_help_name, "r");
    while(fread(&symbol, 1, 1, f_help) && symbol!= EOF) {
        fwrite(&symbol, sizeof(char), 1, f);
    }
    fclose(f);
    fclose(f_help);
}

void menu()
{
    FILE * file, * file_help;
    char f[] = "f.txt";
    char f_help[] = "f_help.txt";
    int Exit = 1;
    int a;
    int pos = 0;
    int che = 0;
    unsigned int key;
    unsigned int par;
    Table * my_tab = create_table();
    while(Exit)
    {
        printf("0.Exit\n1.Add\n2.Find\n3.Delete\n4.Show\n5.Special Delete\n6.Special Find\n7.Special Ex\n");
        a = check(&che);
        if(che != 0)
        {
            a = 0;
        }
        switch (a)
        {
            case 0:
                save_table(my_tab, f);
                file = fopen(f, "w");
                fclose(file);
                file_help = fopen(f_help, "w");
                fclose(file_help);
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
                        my_tab = add_Items(my_tab, key, par, f, f_help);
                        files_copy(f, f_help);
                    } else{
                        printf("Sorry, EOF!!!\n");
                        delete_table(my_tab);
                        file = fopen(f, "w");
                        fclose(file);
                        file_help = fopen(f_help, "w");
                        fclose(file_help);
                        exit(-101);
                    }
                } else
                {
                    printf("Sorry, EOF!!!\n");
                    delete_table(my_tab);
                    file = fopen(f, "w");
                    fclose(file);
                    file_help = fopen(f_help, "w");
                    fclose(file_help);
                    exit(-101);
                }
                break;
            case 2:
                printf("Enter key:");
                key = check(&che);
                if(che == 0)
                {
                    find(my_tab, key, f);
                } else
                {
                    printf("Sorry, EOF!!!\n");
                    delete_table(my_tab);
                    file = fopen(f, "w");
                    fclose(file);
                    file_help = fopen(f_help, "w");
                    fclose(file_help);
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
                    file = fopen(f, "w");
                    fclose(file);
                    file_help = fopen(f_help, "w");
                    fclose(file_help);
                    exit(-101);
                }
                break;
            case 4:
                show(my_tab, f);
                for (int i = 0; i < my_tab -> msize; i++){
                    printf("len %d = %d\n", i, my_tab -> ks[i].info_len);
                }
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
                    file = fopen(f, "w");
                    fclose(file);
                    file_help = fopen(f_help, "w");
                    fclose(file_help);
                    exit(-101);
                }
                break;
            case 6:
                printf("Enter key:");
                key = check(&che);
                if(che == 0)
                {
                    special_find(my_tab, key, f);
                } else
                {
                    printf("Sorry, EOF!!!\n");
                    delete_table(my_tab);
                    file = fopen(f, "w");
                    fclose(file);
                    file_help = fopen(f_help, "w");
                    fclose(file_help);
                    exit(-101);
                }
                break;
            case 7:
                first_special_function(my_tab, f, &pos);
                break;
        }
    }
}
