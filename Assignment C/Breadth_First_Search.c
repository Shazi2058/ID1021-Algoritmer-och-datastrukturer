#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Breadth_First_Search.h"
tree *construct_tree(int val);
void free_tree(tree *tr);
void add(tree **tr, int value);
tree *recursive_add(tree *t, int value);
tree_queue *create_tree_queue();
bool isEmpty(tree_queue *q);
void enqueue(tree_queue *q, tree *t);
tree *dequeue(tree_queue *q);
void free_tree_queue(tree_queue *q);
void breadth_first_search(tree *root);

int main() {
    return 0;
}
tree *construct_tree(int val) {
    tree *tr = (tree*)malloc(sizeof(tree));
    tr->value = val;
    tr->left = NULL;
    tr->right = NULL;
    tr->root = NULL;
    return tr;
}
void free_tree(tree *tr) {
    if (tr != NULL) {
        if (tr->left != NULL) 
            free_tree(tr->left);
        if (tr->right != NULL) 
            free_tree(tr->right);
        free(tr);
    }
}
tree_queue *create_tree_queue() {
    tree_queue *q = (tree_queue*)malloc(sizeof(tree_queue));
    q->first = NULL;
    q->last = NULL;
    return q;
}
bool isEmpty(tree_queue *q) {
    return q->first == NULL;
}
void enqueue(tree_queue *q, tree *t) {
    node *nd = (node*)malloc(sizeof(node));
    nd->tree_pointer = t;
    nd->next = NULL;
    
    if (q->first == NULL) {
        q->first = nd; 
        q->last = nd; 
    } else {
        q->last->next = nd;
        q->last = nd; 
    }
}

tree *dequeue(tree_queue *q) {
    if (q->first == NULL) {
        return NULL;
    }
    node *nd = q->first;
    tree *t = nd->tree_pointer;
    q->first = nd->next;
    if (q->first == NULL) {
        q->last = NULL;
    }
    free(nd);
    return t;
}

void free_tree_queue(tree_queue *q) {
    while (q->first != NULL) {
        dequeue(q);
    }
    free(q);
}

void breadth_first_search(tree *root) {
    if (root == NULL) 
        return;
    tree_queue *q = create_tree_queue(); 
    enqueue(q, root); 
    
    while (!isEmpty(q)) {
        tree *current = dequeue(q);
        printf("%d ", current->value);
        
        if (current->left != NULL) { 
            enqueue(q, current->left); 
        }
        if (current->right != NULL) {
            enqueue(q, current->right); 
        }
    }
    free_tree_queue(q);
}