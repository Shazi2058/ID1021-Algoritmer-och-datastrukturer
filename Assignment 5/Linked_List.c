#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct cell { 
    int value;
    struct cell *tail;
} cell;
typedef struct linked {
    cell *first;
} linked;

linked *linked_create();
void linked_free(linked *lnk);
void linked_add(linked *lnk, int item);
int linked_length(linked *lnk);
bool linked_find(linked *lnk, int item);
void linked_remove(linked *lnk, int item);
void linked_append(linked *a, linked *b);
linked *linked_init(int n);
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);

int main(){
    return 0;
}

linked *linked_create() { 
    linked *new = (linked*)malloc(sizeof(linked));
    new->first = NULL;
    return new;
}

void linked_free(linked *lnk) { 
    cell *nxt = lnk->first;
    while (nxt != NULL) {
        cell *tmp = nxt->tail;
        free(nxt);
        nxt = tmp;
    }
    free(lnk);
}

void linked_add(linked *lnk, int item){
    cell *new = (cell*)malloc(sizeof(cell));
    new->value = item;
    new->tail = lnk->first;
    lnk->first = new;
}

int linked_length(linked *lnk){
    int leng = 0;
    cell *nxt = lnk->first;
    while (nxt != NULL) {
        leng++;
        nxt = nxt->tail;
    }
    return leng;
}

bool linked_find(linked *lnk, int item){
    cell *nxt = lnk->first;
    while (nxt != NULL) {
        if (nxt->value == item) {
            return true;
        }
        nxt = nxt->tail;
    }
    return false;
}

void linked_remove(linked *lnk, int item){
    cell *nxt = lnk->first;
    cell *prev = NULL;
    while (nxt != NULL) {
        if (nxt->value == item) {
            if (prev == NULL) {
                lnk->first = nxt->tail;
            } else {
                prev->tail = nxt->tail;
            }
            break;
        }
        prev = nxt;
        nxt = nxt->tail;
    }
}

void linked_append(linked *a, linked *b) {
    cell *nxt = a->first;
    cell *prev = NULL;
    while(nxt != NULL) {
        prev = nxt;
        nxt = nxt->tail;
    }
    if (prev != NULL){
        prev->tail = b->first;
    }
    else{ 
        a->first = b->first;
    }
    b->first = NULL;
}

linked *linked_init(int n) {
    linked *a = linked_create();
    for (int i = 0; i < n; i++) {
        linked_add(a, i);
    }
    return a;
}

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}