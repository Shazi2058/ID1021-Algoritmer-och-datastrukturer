#include  <stdlib.h>
#include  <stdio.h>
#include  <stdbool.h>
#include  <time.h>
#include  "Trees.h"
#include  "dynamic_stack.h"
#define STACK_SIZE 4
tree *construct_tree();
void free_tree(tree *tr);
node *construct_node(int val);
void free_node(node *nd);
void add(tree *tr, int value);
node *recursive_add(node *nd, int value);
bool lookup(tree *tr, int value);
bool recursive_lookup(node *nd, int value);
void without_recursive_add(tree *tr, int value);
static void print(node *nd);
void print_tree(tree *tr);
stack *create_stack(int size);
void push(stack *stk, node *val);
node* pop(stack *stk);
bool is_stack_empty(stack *stk);
void explicit_print(tree *tr);
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);

int main() {
    return 0;
}
tree *construct_tree() {
    tree *tr = (tree*)malloc(sizeof(tree));
    tr->root = NULL;
    return tr;
}
void free_tree(tree *tr) {
    if (tr != NULL) {
        free_node(tr->root);
        free(tr);
    }
}
node *construct_node(int val) {
    node *nd = (node*)malloc(sizeof(node));
    nd->value = val;
    nd->left = NULL;
    nd->right = NULL;
    return nd;
}
void free_node(node *nd) {
    if (nd != NULL) {
        free_node(nd->left);
        free_node(nd->right);
        free(nd);
    }
}
void add(tree *tr, int value){
    tr->root = recursive_add(tr->root, value);
}
node *recursive_add(node *nd, int value) {
    if (nd == NULL) {
        return construct_node(value);
    }
    if (value == nd->value) {
        return nd;
    }
    if (nd->value > value) {
        nd->left = recursive_add(nd->left, value);
    } else {
        nd->right = recursive_add(nd->right, value);
    }
    return nd;
}

bool lookup(tree *tr, int value) {
    return recursive_lookup(tr->root, value);
}
bool recursive_lookup(node *nd, int value) {
    if (nd == NULL) {
        return false;
    }
    if (nd->value == value) {
        return true;
    }
    if (nd->value > value) {
        return recursive_lookup(nd->left, value);
    } else {
        return recursive_lookup(nd->right, value);
    }
}
void without_recursive_add(tree *tr, int value){
    node *new_node = construct_node(value);
    if (tr->root == NULL) {
        tr->root = new_node;
        return;
    }
    node *current = tr->root;
    node *prv = NULL;
    while (current != NULL) {
        prv = current;
        if (value == current->value) {
            free(new_node);
            return;
        }
        if (current->value > value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (prv->value > value) {
        prv->left = new_node;
    } else {
        prv->right = new_node;
    }
}
static void print(node *nd) {
    if (nd != NULL) {
        print(nd->left);
        printf("%d ", nd->value);
        print(nd->right);
    }
}
void print_tree(tree *tr) {
    if (tr->root != NULL)
        print(tr->root);
    printf("\n");
}
stack *create_stack(int size) {
    stack *stk = (stack*)malloc(sizeof(stack));
    stk->array = (node**)malloc(size * sizeof(node*)); 
    stk->top = 0;
    stk->size = size;
    return stk;
}

void push(stack *stk, node *val) { 
    if (stk->top == stk->size) {
        stk->size *= 2;
        stk->array = realloc(stk->array, stk->size * sizeof(node*));
    }
    stk->array[stk->top++] = val;
}

node* pop(stack *stk) { 
    if (stk->top <= 0) return NULL;
    
    node *val = stk->array[--stk->top];

    if (stk->top > 0 && stk->top <= stk->size / 4 && stk->size > 4) {
        stk->size /= 2;
        stk->array = realloc(stk->array, stk->size * sizeof(node*));
    }
    return val;
}
bool is_stack_empty(stack *stk) {
    return stk->top == 0;
}
void explicit_print(tree *tr) {
    if (tr->root == NULL) {
        return;
    }
    stack *stk = create_stack(STACK_SIZE);
    node *cur = tr->root;
    while (cur->left != NULL) {    
        push(stk, cur);
        cur = cur->left;
    }
    while(cur != NULL) {
        printf("%d ", cur->value);  
        if( cur->right != NULL) {
            cur = cur->right;
            while (cur->left != NULL) {  
                push(stk, cur);
                cur = cur->left;
            }
        } else {
            cur = pop(stk); 
        }
    }
}
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}