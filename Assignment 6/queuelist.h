
typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct queue {
    node *first;
} queue;