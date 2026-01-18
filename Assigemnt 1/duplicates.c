#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}

long duplicates(int n) {

    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        array[i] = rand() % (n * 2);

    int sum = 0;
    struct timespec t_start, t_stop;

    clock_gettime(CLOCK_MONOTONIC, &t_start);

    for (int i = 0; i < n; i++) {
        int key = array[i];
        for (int j = i + 1; j < n; j++) {
            if (key == array[j]) {
                sum++;
                break;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &t_stop);

    free(array);

    if (sum == 0)
        return 0;

    return nano_seconds(&t_start, &t_stop);
}

int main() {

    srand(time(NULL));

    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000};
    int k = 5;

    for (int s = 0; s < 6; s++) {

        int n = sizes[s];
        long min = LONG_MAX;

        for (int i = 0; i < k; i++) {
            long wall = duplicates(n);
            if (wall < min)
                min = wall;
        }

        printf("%d %ld ns\n", n, min);
    }

    return 0;
}