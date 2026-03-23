#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#define MOD 53
#define BUFFER 200


typedef struct connection connection;
typedef struct city city;
typedef struct map map;
void connect(city *src, city *dst, int time); 
int hash(char *name, int mod);
city* lookup(city **cities, char *name);
map *graph(char *file);
int search(city* from, city* to, int limit);
int search_Improved(city *from, city *to, city **path, int k);
int search_dynamic(city *from, city *to,city **path,int k,int current_time,int *best);
bool loop(city **path, int k, city *dest);
long nano_seconds(struct timespec *t_start, struct timespec *t_stop);
// Run = ./train_map Stockholm Umeå 
typedef struct city {
    char* name;
    connection* first;
    struct city *next;
}city;
typedef struct connection {
    struct city* destination_city;
    int time;
    struct connection* next;
}connection;
typedef struct map {
    city **cities;
} map;


int main(int argc, char* argv[]) {

    map *trains = graph("MAP.csv");

    if (argc < 3) {
        printf("usage: %s <from> <to>\n", argv[0]);
        exit(1);
    }

    city *from = lookup(trains->cities, argv[1]);
    city *to   = lookup(trains->cities, argv[2]);
    if (!from || !to) {
        printf("City not found!\n");
        exit(1);
    }

    city *path[100];
    int best = INT_MAX;

    struct timespec t_start, t_stop;
    clock_gettime(CLOCK_MONOTONIC, &t_start);

    int s = search_dynamic(from, to, path, 0, 0, &best);

    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    long wall = nano_seconds(&t_start, &t_stop);

    if (s >= 0)
        printf("Shortest path %d found in %.2fms\n",
               best, ((double)wall)/1000000);
    else
        printf("No path found\n");

    return 0;
}


void connect(city *src, city *dst, int time) {
    connection* ab = (connection*)malloc(sizeof(connection));
    connection* ba = (connection*)malloc(sizeof(connection));

    ab->destination_city = dst;
    ab->time = time;
    ab->next = NULL;

    ba->destination_city = src;
    ba->time = time;
    ba->next = NULL;

    if (src->first == NULL) {
        src->first = ab;
    } else {
        connection *n1 = src->first;
        while (n1->next != NULL) {
            n1 = n1->next;
        }
        n1->next = ab; 
    }
    if (dst->first == NULL) {
        dst->first = ba;
    } else {
        connection *n2 = dst->first;
        while (n2->next != NULL) {
            n2 = n2->next;
        }
        n2->next = ba; 
    }
}
int hash(char *name, int mod) {
    int h = 0;
    int i = 0;
    unsigned char c = 0;
    while((c = name[i]) != 0) {
        h = (h*31 + c) % mod;
        i++;
    }
    return h;
}
city* lookup(city **cities, char *name){
    int index= hash(name, MOD);
    city *cur = cities[index];
    while (cur != NULL){
        if(strcmp(cur->name, name) == 0){ //if the city is found
            return cur;
        }
        cur = cur->next;
    }
    city *new_city = (city*)malloc(sizeof(city));
    new_city->name = strdup(name);
    new_city->first = NULL;
    new_city->next = cities[index];
    cities[index] = new_city;
    return new_city;
}
map *graph(char *file) {
    city **cities = malloc(sizeof(city*) * MOD);
    for (int i = 0; i < MOD; i++) cities[i] = NULL;
    map *trains = (map*)malloc(sizeof(map));
    trains->cities = cities;
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        perror("Error opening file");
        return NULL;
    }
    char *lineptr = malloc(sizeof(char)*BUFFER);
    size_t n = BUFFER;
    while(getline(&lineptr, &n, fptr) > 0) {
        char *src_name = strtok(lineptr, ",");
        char *dst_name = strtok(NULL, ",");
        char *dist_str = strtok(NULL, ",");
        if(src_name && dst_name && dist_str) {
            city *src = lookup(cities, src_name);
            city *dst = lookup(cities, dst_name);
            int dist = atoi(dist_str);
            connect(src, dst, dist);
        }
    } 
    fclose(fptr);
    free(lineptr); 
    return trains;
}
int search(city* from, city* to, int limit) {
    if (from == to) 
        return 0;
    int found = -1;
    connection *n = from->first;
        while(n != NULL){
        if(n->time <= limit){
            int d = search(n->destination_city, to, limit - n->time);
        if (d >= 0 && (found == -1 || (d + n->time) < found))
            found = (d + n->time);
        }
        n = n->next;
    }
    return found;
}
int search_Improved(city *from, city *to, city **path, int k) {
    if (from == to) 
        return 0;
    path[k] = from;
    k++; 
    int found = -1;
    connection *nxt = from->first;
    while (nxt != NULL) {
        if (!loop(path, k, nxt->destination_city)) {
                int d = search_Improved(nxt->destination_city, to, path, k);
                if (d >= 0) {
                    if (found == -1 || (d + nxt->time) < found) {
                        found = d + nxt->time;
                    }
                }
        }
        nxt = nxt->next;
    }
    return found;
}
#include <limits.h>

int search_dynamic(city *from, city *to, city **path, int k, int current_time, int *best) {
    if (from == to) {
        if (current_time < *best) {
            *best = current_time;
        }
        return current_time;
    }
    if (current_time >= *best) {
        return -1;
    }
    path[k] = from; 
    int sofar_best = -1;
    connection *nxt = from->first;
    while (nxt != NULL) {
        if (!loop(path, k, nxt->destination_city)) {
            int result = search_dynamic(nxt->destination_city, to, path, k + 1, current_time + nxt->time, best);
            if (result != -1) {
                if (sofar_best == -1 || result < sofar_best) {
                    sofar_best = result;
                }
            }
        }
        nxt = nxt->next;
    }

    return sofar_best;
}


bool loop(city **path, int k, city *dest) {
    for (int i = 0; i < k; i++) {
        if (path[i] == dest) {
            return true;
        }
    }
    return false;
}

long nano_seconds(struct timespec *t_start, struct timespec *t_stop) {
    return (t_stop->tv_sec - t_start->tv_sec) * 1000000000L +
           (t_stop->tv_nsec - t_start->tv_nsec);
}