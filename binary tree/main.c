#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "readline/readline.h"
int main(){
	struct node *el = calloc(1, sizeof(struct node));
	el -> root = NULL;
	int key, n;
	int exit = 0;
    FILE *f;
    char *name_of_file; // поменять на *
    int number_key, number_info;
    char number_text[11];
    char * mr = "";
    int key_info = 0;
    while(exit == 0){
	    printf("\n 1.Add element\n 2.Delete elements\n 3.Obhod\n 4.Search\n 5.Special search\n 6.Add from File\n 7.Exit\n");
        scanf("%d", &n);
        switch (n) {
            case 1:
	        	el = add_elements(el);
                printf("%d\n", el->info);
                break;
	        case 2:
		//	printf("%s", mr);
		        printf("Enter key ");
		//	mr = "You are wrong? repeate please!";
                      scanf("%d", &key);
			//if (get_int(&key) == 0){
		//	del_tree(el);
		//	return 0;
		//	} while (key < 1){
		        el = delete(el, key);
			break;
			
	        case 3:
	            postfix(el);
                break;
	        case 4:
                printf("Enter key ");
                scanf("%d", &key);
                struct node *el_found;
                el_found = search(el, key);
                break;
	        case 5:
                printf("Enter key\n");
                scanf("%d", &key);
                special_search(el, key);
                break;
            case 6:
                while (1) {
                    printf("Enter name of file\n");
                    name_of_file = readline(NULL);
                    f = fopen(name_of_file, "r");
                    if (f != NULL)
                        break;
                }
                while((fgets(number_text, 11, f))!=NULL)
                {
                    if(key_info == 0){
                        key_info = 1;
                        number_key = atoi(number_text);
                    } else {
                        key_info = 0;
                        number_info = atoi(number_text);
                        el = add_elements_from_file(el, number_key, number_info);
                    }
                }
                fclose(f);
                break;
	        case 7:
                delete_tree(el);
		        exit = 1;
        }
	}
	return 0;
}
