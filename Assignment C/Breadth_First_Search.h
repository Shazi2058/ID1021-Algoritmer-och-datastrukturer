typedef struct tree {
    int value;
    struct tree *root;
    struct tree *left;
    struct tree *right;
} tree;
typedef struct node {
    tree *tree_pointer;
    struct node *next;
} node;

typedef struct tree_queue {
    node *first;
    node *last;
} tree_queue;

