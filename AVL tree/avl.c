#include "avl.h"

int get_height(struct node *el){
    if(el == NULL)
        return (-1);
    else
        return (el -> height);
}

struct node * right(struct node *el) // правый поворот вокруг el
{
    struct node *el_1 = el->left;
    el->left = el_1->right;
    el_1->right = el;
    if(get_height(el->left) > get_height(el->right))
        el->height = get_height(el->left) + 1;
    else
        el->height = get_height(el->right) + 1;

    if(get_height(el_1->left) > get_height(el_1->right))
        el_1->height = get_height(el_1->left) + 1;
    else
        el_1->height = get_height(el_1->right) + 1;

    return el_1;
}

struct node *left(struct node *el){
    struct node *el_1 = el->right;
    el->right = el_1->left;
    el_1->left = el;
    if(get_height(el->left) > get_height(el->right))
        el->height = get_height(el->left) + 1;
    else
        el->height = get_height(el->right) + 1;

    if(get_height(el_1->left) > get_height(el_1->right))
        el_1->height = get_height(el_1->left) + 1;
    else
        el_1->height = get_height(el_1->right) + 1;
    return el_1;
}

struct node *balancing(struct node *el){
    if (get_height(el->left) > get_height(el->right))
        el->height = get_height(el->left) + 1;
    else
        el->height = get_height(el->right) + 1;

    if(get_height(el->right) - get_height(el->left) == 2 ){
        if( get_height(el->right->right) - get_height(el->right->left) < 0 )
            el->right = right(el->right);
        return left(el);
    }
    if( get_height(el->right) - get_height(el->left) == -2 ){
        if( get_height(el->left->right) - get_height(el->left->left) > 0  )
            el->left = left(el->left);
        return right(el);
    }
    return el;
}

//struct node *add_elements(struct node* el){
//    int key;
//    int info;
//
//    el = add_element(el, key, info);
//    return(el);
//}

struct node *add_element(struct node *el, int key, char * info){
    if (el == NULL){
        el = calloc(1, sizeof(struct node));
        el->key = key;
      //  el->info = calloc(81, sizeof(char));
	el->info = info;
        el->height = 0;
    } else {
        if (el->key > key)
            el->left = add_element(el->left, key, info);
        else
            el->right = add_element(el->right, key, info);
    }
    el = balancing(el);
    return el;
}

void postfix(struct node *el){
    if(el == NULL)
        return;
    postfix(el -> left);
    postfix(el -> right);
    printf("%d|%s|%d  ", el -> key, el -> info, el -> height);
}

struct node * search (struct node * el, int  key){
    if (el -> key == key){
        printf("Element is found - %d | %s\n", el -> key, el -> info);
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
        printf("Element is found - %d | %s\n", el -> key, el -> info);
        return;
    }
    if (el -> key < key){
        if (el -> right){
            special_search(el->right, key);
        } else{
            printf("Special element - %d | %s\n", el->key, el->info);
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

struct node *delete_min(struct node *el){
    if (el -> left == NULL )
        return el -> right;
    el -> left = delete_min(el -> left);
    return balancing(el);
}

struct node *delete(struct node *el, int key){
    if (el == NULL)
        return NULL;
    if (el -> key > key)
        el -> left = delete(el -> left, key);
    else if (el -> key < key)
        el -> right = delete(el -> right, key);
    else{
        struct node *el_1 = el -> left;
        struct node *el_2 = el -> right;
        free(el);
        if(el_2 == NULL)
            return el_1;
        struct node *min = min_el(el_2);
        min -> right = delete_min(el_2);
        min -> left = el_1;
        return balancing(min);
    }
    return balancing(el);
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
