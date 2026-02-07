#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000

long nano_seconds(struct timespec *t_start, struct timespec *t_stop);
bool recursive(int array[], int length, int key, int first, int last);
int *sorted(int n);


int main() {
    srand(time(NULL));

    int *array = sorted(MAX_SIZE);
    int length = MAX_SIZE;

    int key = -1;  // Use a value unlikely to exist for consistent timing

    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);

    bool found = recursive(array, length, key, 0, length - 1);

    clock_gettime(CLOCK_MONOTONIC, &t_stop);

    long elapsed = nano_seconds(&t_start, &t_stop);
    printf("Elapsed time: %ld nanoseconds\n", elapsed);

    if (found) {
        printf("Key %d found in the array.\n", key);
    } else {
        printf("Key %d not found in the array.\n", key);
    }

    free(array);
    return 0;
}
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}
int *sorted(int n) {
    int *array = (int*)malloc(n * sizeof(int));
    int nxt = 0;
    for (int i = 0; i < n; i++) {
        nxt += rand() % 10 + 1;
        array[i] = nxt;
    }
    return array;
}

bool recursive(int array[], int length, int key, int first, int last) {
    int index = (first + last) / 2; // jump to the middle
    if (array[index] == key) {
        return true; 
    }
    if (array[index] < key && index < last) {
    // call recursive but narrow the search
        return recursive(array, length, key, index + 1, last);
    }
    if (array[index] > key && index > first) {
    // call recursive but narrow the search
        return recursive(array, length, key, first, index - 1);
    }
        return false; // as before
} 