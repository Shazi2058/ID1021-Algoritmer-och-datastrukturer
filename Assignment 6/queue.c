#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "queuelist.h"
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
    return q;
}
bool empty(queue *q) { // is the queue empty?
    return q->first == NULL;
}
void enque(queue* q, int v) {
    node *nd = (node*)malloc(sizeof(node));
    nd->value = v;
    nd->next = NULL;
    node *prv = NULL;
    node *nxt = q->first;
    while (nxt != NULL) { 
        prv = nxt;
        nxt = nxt->next;
    }
    if (prv == NULL) {
        q->first = nd;
    } else {
        prv->next = nd;
    }
}
int dequeue(queue *q) {
    int res = 0;
    if (q->first != NULL) {
        node *nd = q->first; 
        res = nd->value;
        q->first = nd->next;
        free(nd);
    }
    return res;
}
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}