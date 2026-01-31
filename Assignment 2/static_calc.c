#include <stdlib.h>
#include <stdio.h>

typedef struct stack {
    int top;
    int size;
    int *array;
} stack;

stack *new_stack(int size) {
    if (size < 1) {
        fprintf(stderr, "Stack size has to be at least 1\n");
        return NULL;
    }
    int *array = (int*)malloc(size*sizeof(int));
    stack *stk = (stack*)malloc(sizeof(stack));
    
    stk->top = 0;
    stk->size = size;
    stk->array = array;
    return stk;
}
void push(stack *stk, int val) {
    if (stk->top == stk->size) {
        fprintf(stderr, "Stack overflow\n");
        return;
    }
    stk->array[stk->top] = val;  // Place value
    stk->top+=1; // Move the top up
}
int pop(stack *stk) {
    if (stk->top <= 0) {
        fprintf(stderr, "Stack underflow\n");
        return 0;
    }
    stk->top-=1; //Move top down 
    int val = stk->array[stk->top]; // Get the value
    return val; // return the value
}
int main() {
    stack *stk = new_stack(4);
    push(stk, 32);
    push(stk, 33);
    push(stk, 34);

    printf("pop : %d\n", pop(stk));
    printf("pop : %d\n", pop(stk));
    printf("pop : %d\n", pop(stk));

    return 0;
}