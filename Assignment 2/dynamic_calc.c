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
    if (stk == NULL) {
        free(array);
        return NULL;
    }
    stk->top = 0;
    stk->size = size;
    stk->array = array;
    return stk;
}
void push(stack *stk, int val) {
    if (stk->top == stk->size) {
        int size = stk->size * 2;//doubling the size
        int *copy=(int*)malloc( size * sizeof(int)); // New array
        for (int i = 0; i < stk->size; i++) { // Copy old values
            copy[i] = stk->array[i];
        }
        free(stk->array); // Free old array
        stk->array = copy; // Point to new array
        stk->size = size; // Update size
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
    int val = stk->array[stk->top];
        if (stk->top <= stk->size / 4 && stk->size > 4) {
        int size = stk->size / 2; // Halve the size
        int *copy = (int*)malloc(size * sizeof(int)); // New array
        for (int i = 0; i < stk->top; i++) { // Copy old values
            copy[i] = stk->array[i];
        }
        free(stk->array); // Free old array
        stk->array = copy; // Point to new array
        stk->size = size; // Update size
    }
    return val; // return the value
}

int main() {
    stack *stk = new_stack(4);
    int n = 10;
    for(int i = 0; i < n; i++) {
        push(stk, i+30);
    }
    for(int i = 0; i < stk->top; i++) {
        printf("stack[%d] : %d\n", i, stk->array[i]);
    }
    int val = pop(stk);
    while(val != 0) { // assuming 0 is returned when the stack is empty
        printf("pop : %d\n", val);
        val = pop(stk);
    }
    return 0;
}
