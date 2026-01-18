#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}
long bench(int n, int loop) {

    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        array[i] = i;

    int *indx = malloc(loop * sizeof(int));
    for (int i = 0; i < loop; i++)
        indx[i] = rand() % n;

    int sum = 0;
    struct timespec t_start, t_stop;

    clock_gettime(CLOCK_MONOTONIC, &t_start);

    for (int i = 0; i < loop; i++)
        sum += array[indx[i]];

    clock_gettime(CLOCK_MONOTONIC, &t_stop);

    free(array);
    free(indx);

    if (sum == 0)
        return 0;

    return nano_seconds(&t_start, &t_stop);
}

int main() {

    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000};
    int loop = 1000;
    int k = 10;

    for (int s = 0; s < 6; s++) {

        int n = sizes[s];
        long min = LONG_MAX;

        for (int i = 0; i < k; i++) {
            long wall = bench(n, loop);
            if (wall < min)
                min = wall;
        }

        printf("%d %0.2f ns\n", n, (double)min / loop);
    }

    return 0;
}
