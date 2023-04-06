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

    if(!table)
    {
        printf("Ssory, memory error(((\n");
        exit(-101);
    }

    printf("Enter size of your table:");
    table -> msize = check(&che);

    if(che == 0)
    {
        table -> csize = 0;
        Keyspace * ks = calloc(table -> msize, sizeof(Keyspace));

        if(!ks)
        {
            printf("Sorry, memory ERROR!!!\n");
            free(table);
            exit(-101);
        }

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

int hash_func(char * key, int msize)
{
    int pos = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        pos += key[i];
    }
    return pos % msize;
}

void reorg_table(Table * table, int * help){
    for (int i = 0; i < table->msize; i++){
        if(table->ks[i].rel_size > 1){
            Elem * el = table->ks[i].head;
            Elem * el1 = el;
            while (el->next != NULL){
                el = el->next;
                free(el1->info);
                free(el1->key);
                free(el1);
                table->ks[i].head = el;
                el1 = el;
            }
            (table->csize)-=(el->release-1);
            el->release = 1;
            table->ks[i].rel_size = 1;
            (*help)++;
        }
    }
}

void add_elem(Table * table, char * key, char * info, int *help)
{
    int help_1 = 0;
    int pos = 0;
    if(table->msize > table->csize)
    {
        Elem * el = calloc(1, sizeof(Elem));
        if(!el){
            printf("Sorry, memory ERROR((\n");
            //delete_table(table);
            exit(-101);
        }
        pos = hash_func(key, table->msize);

        if(!table->ks[pos].head)
        {
            table->ks[pos].head = el;
            el->key = key;
            el->info = info;
            el->next = NULL;
            el->release = 1;
            (table->ks[pos].rel_size)++;
            (table->csize)++;
            return;
        } else {
            Elem * el1 = table->ks[pos].head;
            while (el1 -> next != NULL){
                el1 = el1->next;
            }
            el1 -> next = el;
            el->key = key;
            el->info = info;
            el->next = NULL;
            el->release = table->ks[pos].rel_size + 1;
            (table->ks[pos].rel_size)++;
            (table->csize)++;
            return;
        }
    } else {
        int code = 1;
        int a;
        int che = 0;

        while (code){
            printf("1.Reorganization\n2.Not redact Table\n");
            a = check(&che);
            if(che != 0)
            {
                printf("Sorry, EOF!!!\n");
                //delete_table(table);
                exit(-101);
            }
            switch (a) {
                case 1:
                    reorg_table(table, &help_1);
                    if(help_1 != 0)
                    {
                        (*help)++;
                    } else {
                        printf("Sorry, msize = csize, you can't add_elem\n");
			free(key);
			free(info);
                    }
                    return;
                case 2:
                    free(key);
                    free(info);
                    return;
            }
        }
    }
}

void show(Table * table)
{
    printf("_____________________________\n");
    printf("release|  key  |  info \n");
    for(int i = 0; i < table -> msize; i++)
    {
        if(table->ks[i].rel_size > 0) {
            printf("_____________________________\n");
            Elem* el = table->ks[i].head;
            for (int j = 0; j < table->ks[i].rel_size; j++)
            {
                printf("   %d   | %s | %s\n", el->release, el->key, el->info);
                el = el->next;
            }
        }
    }
    printf("_____________________________\n");
}

void find(Table* table, char * key)
{
    int pos = hash_func(key, table->msize);

    if(!table->ks[pos].head)
    {
        printf("Elem is not exist\n");
	free(key);
        return;
    } else {
        Elem  * el = table->ks[pos].head;
        printf("_____________________________\n");
        printf("release|  key  |  info \n");
        for (int i = 0; i < table->ks[pos].rel_size; i++){
            if(strcmp(key, el->key) == 0) {
                printf("_____________________________\n");
                printf("   %d   | %s | %s\n", el->release, el->key, el->info);
            }
            el = el->next;
        }
	free(key);
        printf("_____________________________\n");
    }
}

void delete(Table * table, char * key)
{
    int pos = hash_func(key, table->msize);
    int del = 0;

 //   printf("\n\n\n %d\n\n\n", pos);
    if(!table->ks[pos].head)
    {
        printf("Elem is not exist!\n");
	free(key);
        return;
    } 
   
//	printf("\n\n\n\n\nPIDOR");
    Elem * a = table->ks[pos].head;
        Elem * b = a;
    
        for (int i = 0; i < table->ks[pos].rel_size; i++)
        {
            b = b -> next;

            if(strcmp(a->key, key) == 0 && a == table->ks[pos].head)
            {
                del++;
                free(a->key);
	//	a->key = NULL;
                free(a->info);
               // a -> next = NULL;
                free(a);
                table->ks[pos].head = b;
            // a = b;
		if(b){
	      		 b->release = i + 1;
	     	  }
            } else if(strcmp(b->key, key) == 0){
                del++;
                a ->next = b -> next;
                free(b->key);
	//	b->key = NULL;
                free(b->info);
               // b -> next = NULL;
                free(b);
                b = a -> next;
		if(b){
                b -> release = i + 1;
	        }
            } else if(del > 0) {
                b ->release = i + 1;
            }
            a = b;
        }
        table->ks[pos].rel_size -= del;
        free(key);
    if(del == 0){
    	printf("Element is not exist\n");
    }
}

void delete_table(Table * table)
{
    for (int i = 0; i < table->msize; i++)
    {
        if(table->ks[i].head)
        {
            Elem * a = table->ks[i].head;
            Elem * b = a;
            for (int j = 0; j < table->ks[i].rel_size; j++)
            {
                b = b->next;
                free(a->key);
                free(a->info);
                free(a);
                a = b;
            }
        }
    }
    free(table->ks);
    free(table);
}

void menu()
{
    int Exit = 1;
    int a;
    int help = 0;
    int che = 0;
    char * key;
    char * info;
    Table * my_tab = create_table();
    while(Exit)
    {
        printf("0.Exit\n1.Add\n2.Special Find\n3.Delete\n4.Show\n");
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
                printf("Enter key:\n");
                getchar();
                key = f_readline();
                if(key == NULL){
                    printf("Sorry, EOF!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                printf("Enter info:\n");
                info = f_readline();
                if(info == NULL){
                    printf("Sorry, EOF!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                add_elem(my_tab, key, info, &help);
                if(help != 0){
                    add_elem(my_tab, key, info, &help);
		  //  free(key);
                    help = 0;
                }
                //free(key);
                //free(info);
                break;
            case 2:
                printf("Enter key:\n");
                getchar();
                key = f_readline();
                if(key == NULL){
                    printf("Sorry, EOF!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                find(my_tab, key);
               // free(key);
                break;
            case 3:
                printf("Enter key:\n");
                getchar();
                key = f_readline();
                if(key == NULL){
                    printf("Sorry, EOF!!\n");
                    delete_table(my_tab);
                    exit(-101);
                }
                delete(my_tab, key);
	//	free(key);
                break;
            case 4:
                show(my_tab);
                break;
        }
    }
}
