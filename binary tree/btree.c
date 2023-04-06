#include "btree.h"

int get_int(int *a){
	int n;
	do{
	   n = scanf("%d", a);
		if(n < 0)
			return 0;
		if (n == 0){
				printf("Error! Repeat input\n");
				scanf("%*s");
			}
		} while (n == 0);{
		return 1;}
}

struct node *add_elements(struct node * el){
    int key;
    int info;
    if (el -> root == NULL){
        printf("Enter root of your tree\n");
        printf("Enter key\n");
        scanf("%d", &key);
        printf("Enter info\n");
        scanf("%d", &info);
        el -> key = key;
        el -> info = info;
        el -> root = el;
        return(el);
    } else {
        printf("Enter new elements of your tree\n");
        printf("Enter key\n");
        scanf("%d", &key);
        printf("Enter info\n");
        scanf("%d", &info);
        struct node *el_new = calloc(1, sizeof(struct node));
        el_new -> key = key;
        el_new -> info = info;
        el_new -> root = el -> root;
        add_element(el, el_new);
        return(el -> root);
    }

}

struct node *add_elements_from_file(struct node * el, int key, int info){
    if (el -> root == NULL){
        el -> key = key;
        el -> info = info;
        el -> root = el;
        return(el);
    } else {
        struct node *el_new = calloc(1, sizeof(struct node));
        el_new -> key = key;
        el_new -> info = info;
        el_new -> root = el -> root;
        add_element(el, el_new);
        return(el -> root);
    }
}

void add_element(struct node * el, struct node * el_new){
    if(el -> key > el_new -> key ) {
        if(el -> left)
            add_element(el -> left, el_new);
        else
            el->left = el_new;
    }
    if(el -> key < el_new -> key) {
        if(el -> right)
            add_element(el -> right, el_new);
        else
            el->right = el_new;
    }
    if(el -> key == el_new -> key){
        printf("Polzovatel debil\n");
        free(el_new);
        add_elements(el->root);
    }

}

void postfix(struct node *el){
    if(el == NULL)
        return;
    postfix(el -> left);
    postfix(el -> right);
    printf("%d|%d  ", el -> key, el -> info);
}

struct node * search (struct node * el, int key){
    if (el -> key == key){
        printf("Element is found - %d | %d\n", el -> key, el -> info);
        return el;
    } else if (el -> key < key){
        if (el -> right){
            search(el->right, key);
        } else {
            printf("Element does't exist\n");
            return NULL;
        }
    } else if (el -> key > key){
        if (el -> left){
            search(el->left, key);
        } else {
            printf("Element does't exist\n");
            return NULL;
        }
    }
}

struct node * help_search(struct node * el, int key){
    struct node *prev;
    if (el -> key < key) {
        if ((el -> right) && (el -> right) -> key != key){
            prev = help_search(el -> right, key);
        } else if ((el -> right) && (el -> right) -> key == key){
            return el;
        } else {
            return NULL;
        }
    } else if (el -> key > key){
        if ((el -> left) && (el -> left) -> key != key){
            prev = help_search(el -> left, key);
        } else if ((el -> left) && (el -> left) -> key == key){
            printf("EL - %d\n", el->key);
            return el;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
    return prev;
}

void special_search (struct node * el, int key){
    if (el -> key == key){
        printf("Element is found - %d | %d\n", el -> key, el -> info);
        return;
    }
    if (el -> key < key){
        if (el -> right){
            special_search(el->right, key);
        } else{
            printf("Special element - %d | %d\n", el->key, el->info);
            return;
        }

    }
    if (el -> key > key){
        if (el -> left){
            special_search(el->left, key);
        } else{
            printf("I apologies, but special element doesn't exist\n");
            return;
        }
    }
}

struct node * min_el(struct node * el){
    struct node *min;
    if (el -> left){
        min  = min_el(el->left);
    } else {
        return (el);
    }
    return (min);
}

void root_changes(struct node * el, struct node * root){
    if(el == NULL)
        return;
    root_changes(el -> left, root);
    root_changes(el -> right, root);
    el -> root = root;
}

struct node * delete(struct node * el, int key){
    struct node * s = search(el, key);
    struct node *l, *a;
    l = help_search(el, key);
    if (s != el -> root){
        if (s == NULL){
            printf("Element doesn't exist!");
        } else {
            if ((s -> right == NULL) && (s -> left == NULL)){
                if (l -> left && l -> left == s){
                    l -> left = NULL;
                }
                else if (l -> right && l -> right == s){
                    l -> right = NULL;
                }
                free(s);
                return el;
            } else {
                if (s -> left && !(s -> right)) {
                    if (l->left == s) {
                        l->left = s->left;
                        free(s);
                    } else if (l->right == s) {
                        l->right = s->left;
                        free(s);
                    }
                } else if (!(s -> left) && s -> right){
                    if (l -> left == s){
                        l -> left = s -> right;
                        free (s);
                    } else if (l -> right == s){
                        l -> right = s -> right;
                        free (s);
                    }
                } else if (s -> left && s -> right){
                    if (l -> left == s){
                        a = min_el(s -> right);
                        help_delete(el, a);
                        l -> left = a;
                        a -> left = s -> left;
                        a -> right = s -> right;
                        free (s);
                    } else if (l -> right == s){
                        a = min_el(s -> right);
                        l -> right = a;
                        a -> left = s -> left;
                        a -> right = s -> right;
                        free (s);
                    }
                }
            }
        }
    } else {
        if (s == NULL){
            printf("Element doesn't exist");
        } else {
            if (!(s -> right) && !(s -> left)){
                free (s);
                return NULL;
            } else if (s -> left && !(s -> right)){
                root_changes(el, s -> left);
                el = s -> left;
                free (s);
                return el;
            } else if (!(s -> left) && s -> right){
                a = min_el(s -> right);
                if (s -> right -> left) {
                    help_delete(el, a);
                    a -> right = s -> right;
                } else
                    a = s -> right;
                root_changes(el, a);
                el = a;
                free (s);
                return el;
            }else if (s -> left && s -> right){
                a = min_el(s -> right);
                if (s -> right -> left) {
                    help_delete(el, a);
                    a -> right = s -> right;
                } else
                    a = s -> right;
                a -> left = s -> left;
                el = a;
                root_changes(el, a);
                free (s);
                return el;
            }
        }
    }
    return el;
}

void help_delete(struct node * el, struct node * a){
    struct node * t;
    if (!(a -> right)){
        t = help_search(el, a -> key);
        t -> left = NULL;
    } else {
        t = help_search(el, a -> key);
        t -> left = a -> right;
    }
}

void delete_tree(struct node *el){
    if (el){
        if (el -> left)
            delete_tree(el -> left);
        if (el -> right)
            delete_tree(el -> right);
        free(el);
    }
}

