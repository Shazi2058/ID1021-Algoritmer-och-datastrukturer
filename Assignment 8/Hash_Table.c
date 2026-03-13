#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define AREAS 20000
#define BUFFER 200

typedef struct area { 
    char *name;
    int zip; 
    int pop;
} area;
typedef struct codes { 
    area *areas;
    int n;
} codes;
typedef struct node {
    area *data;
    struct node *next;
} node;

codes *read_postcodes(char *file);
bool binary_search(area array[], int length, int key);
bool linear_search(area array[], int length, int key);
int direct_access(area *direct[], int key);
void collisions(codes *postnr, int mod);
node *create_node(area *data);
void free_node(node *n);
area* hash_lookup(node *table[], int key);
area* better_hash_lookup(area *table[], int key);
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);


int main() {
    codes *postnr = read_postcodes("zip_codes.csv");
    return 0;
}
node *create_node(area *data) {
    node *new = (node*)malloc(sizeof(node));
    new->data = data;
    new->next = NULL;
    return new;
}
void free_node(node *n) {
    free(n->data);
    free(n);
}
codes *read_postcodes(char *file) {
    codes *postnr = (codes*)malloc(sizeof(codes));
    area *areas = (area*)malloc(sizeof(area)*AREAS);
    FILE *fptr = fopen(file, "r");
    int k = 0;
    char *lineptr = malloc(sizeof(char)*BUFFER);
    size_t n = BUFFER;
    while((k < AREAS) && (getline(&lineptr, &n, fptr) > 0)) {
        char *copy = (char*)malloc(sizeof(char)*n);
        strcpy(copy, lineptr);
        area a;
        char *zip = strtok(copy, ",");
        a.zip = atoi(zip)*100 + atoi(zip+3);
        a.name = strtok(NULL, ",");
        a.pop = atoi(strtok(NULL, ","));
        areas[k++] = a;
    }
    fclose(fptr);
    postnr->areas = areas;
    postnr->n = k;
    return postnr;
}
bool linear_search(area array[], int length, int key) {
    for (int i = 0; i < length; i++) {
        if (array[i].zip == key) {
            return true;
        }
    }
    return false;
}

bool binary_search(area array[], int length, int key) {
    int first = 0;
    int last = length - 1;
    while (first <= last) {
        int mid = first + (last - first) / 2;
        int cmp = array[mid].zip - key;
        
        if (cmp == 0) return true;
        if (cmp < 0) first = mid + 1;
        else last = mid - 1;
    }
    return false;
}
int direct_access(area *direct[], int key) {
    if (key < 0 || key >= AREAS) 
        return -1;
    if (direct[key]) 
        return direct[key]->zip; 
    return -1; 
}
void collisions(codes *postnr, int mod) {
    int mx = 20; 
    int data[mod]; 
    int cols[mx]; 
    for(int i = 0; i < mod; i++) {
        data[i] = 0;
    }
    for(int i = 0; i < mx; i++) {
        cols[i] = 0;
    }
    for (int i = 0; i < postnr->n; i++) {
        int index = (postnr->areas[i].zip)%mod;
        data[index]++;
    }
    int sum = 0;
    for(int i = 0; i < mod; i++) {
        sum += data[i]; 
        if (data[i] < mx)
            cols[data[i]]++;
    }
    printf("%d (%d) : ", mod, sum);
    for (int i = 1; i < mx; i++) {
        printf("%6d ",cols[i]);
    }
    printf("\n");
}
area* hash_lookup(node *table[], int key) {
    int index = key % AREAS;
    node *current = table[index];
    while (current != NULL) {
        if (current->data->zip == key) {
            return current->data; 
        }
        current = current->next;
    }
    return NULL; 
}
area* better_hash_lookup(area *table[], int key){
    int count = 0;
    int index = key % AREAS;
    while (table[index] != NULL) {
        if (table[index]->zip == key) {
            return table[index]; 
        }
        index = (index + 1) % AREAS; 
        count++;
        if (count >= AREAS) { 
            break;
        }
    }
    return NULL;
}
long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_nsec - t_start->tv_nsec) +
           (t_stop->tv_sec - t_start->tv_sec) * 1000000000;
}