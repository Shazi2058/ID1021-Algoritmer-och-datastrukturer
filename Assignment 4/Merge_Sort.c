#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 25000

long nano_seconds(struct timespec *t_start, struct timespec *t_stop);
void mergesort(int *org, int n);
void sort(int *org, int *aux, int lo, int hi);
void merge(int *org, int *aux, int lo, int mid, int hi);

int main() {
    int array[MAX_SIZE];
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = rand() % 10; 
    }
    mergesort(array, MAX_SIZE);
    printf("Sorted Done Successfully\n");
    printf("\n");
    return 0;
}

void mergesort(int *org, int n) {
    if (n == 0)
    return "noting to sort";
    int *aux = (int*)malloc(n * sizeof(int));
    sort(org, aux, 0, n-1);
    free(aux);
}
void sort(int *org, int *aux, int lo, int hi) {
    if (lo != hi) {
        int mid = (lo + hi)/2;
        sort(org, aux, lo, mid); 
        sort(org, aux, mid+1, hi); 
        merge(org, aux, lo, mid, hi); 
    }
}
void merge(int *org, int *aux, int lo, int mid, int hi) {
    for ( int i = lo; i <= hi; i++ ) {
        aux[i] = org[i];
    }
    int i = lo; 
    int j = mid+1; 

    for ( int k = lo; k <= hi; k++) { 
        if (i > mid) { 
            org[k] = aux[j++];
        } else if (j > hi) { 
            org[k] = aux[i++]   ;
        } else if (aux[i] <= aux[j]) { 
            org[k] = aux[i++];
        } else { 
            org[k] = aux[j++];
        }
    }
}
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}
