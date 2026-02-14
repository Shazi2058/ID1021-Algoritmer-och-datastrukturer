#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100000
void selection_sort(int array[], int size);
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);

int main() {
    int array[MAX_SIZE];
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = rand(); 
    }
    selection_sort(array, MAX_SIZE);
    printf("Sorted Done Successfully\n");
    printf("\n");
    return 0;
}
void selection_sort(int array[], int size){
    for (int i = 0; i < size - 1;i++){
        int candidate = i;
        for (int j = i + 1; j < size; j++){
            if (array[j] < array[candidate]){
                candidate = j;
            }
        }
        if (candidate != i){
            int e = array[i];
            array[i] = array [candidate];
            array[candidate] = e;
        }
    }

}
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}
