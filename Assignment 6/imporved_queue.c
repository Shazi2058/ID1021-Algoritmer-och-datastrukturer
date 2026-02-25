#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "imporved_queuelist.h"
queue *create_queue();
bool empty(queue *q);
void enque(queue* q, int v);
int dequeue(queue *q);
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);
int main() {
    return 0;
}
queue *create_queue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->first = NULL;
    q->last = NULL;
    return q;
}
bool empty(queue *q) { // is the queue empty?
    return q->first == NULL && q->last == NULL;
}
void enque(queue* q, int v) {
    node *nd = (node*)malloc(sizeof(node));
    nd->value = v;
    nd->next = NULL;
    
    if (q->first == NULL) { 
        q->first = nd;
    } else {
        q->last->next = nd;
    }
    q->last = nd;
}
int dequeue(queue *q) {
    int res = 0;
    if (q->first != NULL) {
        node *nd = q->first; 
        res = nd->value;
        q->first = nd->next;
        free(nd);
    }
    if (q->first == NULL) {
        q->last = NULL;
    }
    return res;
}
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}
