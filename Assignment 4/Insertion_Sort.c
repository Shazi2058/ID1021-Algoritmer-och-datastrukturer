#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 25000
void insertion_sort(int array[], int size);
void swap(int array[], int a, int b);
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);

int main() {
    int array[MAX_SIZE];
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = rand() % 10; 
    }
    insertion_sort(array, MAX_SIZE);
    printf("Sorted Done Successfully\n");
    printf("\n");
    return 0;
}
void insertion_sort(int array[], int size) {
    for (int i = 1; i < size; i++) {
        for (int j = i; j > 0 && array[j] < array[j - 1]; j--) {
            swap(array, j, j - 1);
        }
    }
}
void swap(int array[], int a, int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}
