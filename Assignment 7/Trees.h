typedef struct node {
    int value;
    struct node *right;
    struct node *left;
} node;
typedef struct tree {
    node *root;
} tree;