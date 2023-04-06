#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(){
    struct node *root = NULL;
	int key, n;
    char * info;
	int exit = 0;
    FILE *f;
    char *name_of_file; // поменять на *
    int number_key;
    char *number_info;
    char number_text[81];
    int key_info = 0;
    while(exit == 0){
	    printf("\n 1.Add element\n 2.Delete elements\n 3.Obhod\n 4.Search\n 5.Special search\n 6.Add from File\n 7.Exit\n");
        scanf("%d", &n);
        switch (n) {
            case 1: // ПРОВЕРКА НА ВВОД
                printf("Enter new elements of your tree\n");
                printf("Enter key\n");
                scanf("%d", &key);
                printf("Enter info\n");
//                scanf("%d", &info);
                info = readline(NULL);
	        	root = add_element(root, key, info);
                break;
	        case 2:
		        printf("Enter key ");
                scanf("%d", &key);
		        root = delete(root, key);
            	break;
	        case 3:
	            postfix(root);
                break;
	        case 4: // ПРОВЕРКА НА ВВОД
                printf("Enter key ");
                scanf("%d", &key);
                struct node *el_found;
                el_found = search(root, key);
                break;
	        case 5: //ПРОВЕРКА НА ВВОД И МБ НАДО ВОЗВРАЩАТЬ ЭЛЕМЕНТЫ
                printf("Enter key\n");
                scanf("%d", &key);
                special_search(root, key);
                break;
            case 6:
                while (1) {
                    printf("Enter name of file\n");
    //                scanf("%s", &name_of_file);
                    name_of_file = readline(NULL);
                    f = fopen(name_of_file, "r");
                    if (f != NULL)
                        break;
                }
                while((fgets(number_text, 81, f))!=NULL)
                {
//			number_info = NULL;
                    if(key_info == 0){
                        key_info = 1;
                        number_key = atoi(number_text);
                    } else {
                        key_info = 0;
                        printf(" HI %s\n", number_text);
			//number_info = ;
                        root = add_element(root, number_key, number_text);
                    }
                }
                fclose(f);
                break;
	        case 7:
                delete_tree(root);
		        exit = 1;
        }
	}
	return 0;
}
