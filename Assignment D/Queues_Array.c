#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define SIZE 2
typedef struct queue {
    int *array;
    int front;
    int last;
    int size;

} queue;
bool empty (queue *q);
void enque(queue* q, int v);
int dequeue(queue *q);
queue *create_queue();
void increase_size(queue *q);
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);
int main() {
    return 0;
}

bool empty (queue *q) {
    return (q->front == q->last);
}
queue *create_queue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->array = (int*)malloc(SIZE * sizeof(int)); 
    if (q->array == NULL) {
        free(q);
        return NULL;
    }
    q->front = 0;
    q->last = 0;
    q->size = SIZE;
    return q;
}
void enque(queue* q, int v) {
    if ((q->last + 1) % q->size == q->front) { 
        increase_size(q);
    }
    q->array[q->last] = v;
    q->last = (q->last + 1) % q->size;
}
int dequeue(queue *q) {
    if (empty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int val = q->array[q->front];
    q->front = (q->front + 1) % q->size;
    return val;
}
void increase_size(queue *q) {
    int size = q->size * 2; 
        int *copy=(int*)malloc( size * sizeof(int)); 
        for (int i = 0; i < q->size; i++) { 
            copy[i] = q->array[i];
        }
        free(q->array);
        q->array = copy; 
        q->size = size; 
    }
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}