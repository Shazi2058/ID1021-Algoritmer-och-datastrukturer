#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <mach/mach_time.h>

#define MAX_SIZE 500000

bool unsorted_search(int array[], int length, int key) {
    for (int index = 0; index < length; index++) {
        if (array[index] == key) {
            return true;
        }
    }
    return false;
}

int main() {
    int array[MAX_SIZE];

    // Seed random generator ONCE
    srand(time(NULL));

    // Fill array with random numbers
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = rand();
    }

    int length = sizeof(array) / sizeof(array[0]);
    int key = rand();   

    mach_timebase_info_data_t timebase_info;
    mach_timebase_info(&timebase_info);

    // START timing
    uint64_t start = mach_absolute_time();

    bool found = unsorted_search(array, length, key);

    // END timing
    uint64_t end = mach_absolute_time();

    uint64_t elapsed = end - start;
    uint64_t nanoseconds = elapsed * timebase_info.numer / timebase_info.denom;

    if (found) {
        printf("Key %d found in the array.\n", key);
    } else {
        printf("Key %d not found in the array.\n", key);
    }

    printf("Time taken: %llu nanoseconds\n", nanoseconds);

    return 0;
}
