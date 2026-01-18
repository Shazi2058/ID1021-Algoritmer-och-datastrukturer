#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}
long search(int n, int loop) {

    int *array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        array[i] = rand() % (n * 2);

    int *keys = malloc(loop * sizeof(int));
    for (int i = 0; i < loop; i++)
        keys[i] = rand() % (n * 2);

    int sum = 0;
    struct timespec t_start, t_stop;

    clock_gettime(CLOCK_MONOTONIC, &t_start);

    for (int i = 0; i < loop; i++) {
        int key = keys[i];
        for (int j = 0; j < n; j++) {
            if (key == array[j]) {
                sum++;
                break;
            }
        }
    }

clock_gettime(CLOCK_MONOTONIC, &t_stop);
long wall = nano_seconds(&t_start, &t_stop);
return wall;
}
int main() {

    srand(time(NULL));

    int sizes[] = {1000, 2000, 4000, 8000, 16000, 32000};
    int loop = 100;
    int k = 10;

    for (int s = 0; s < 6; s++) {

        int n = sizes[s];
        long min = LONG_MAX;

        for (int i = 0; i < k; i++) {
            long wall = search(n, loop);
            if (wall < min)
                min = wall;
        }

        printf("%d %0.2f ns\n", n, (double)min / loop);
    }

    return 0;
}
