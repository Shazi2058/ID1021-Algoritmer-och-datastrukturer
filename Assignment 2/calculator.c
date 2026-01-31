#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct stack {
    int top;
    int size;
    int *array;
} stack;

stack *new_stack(int size) {
    int *array = (int*)malloc(size*sizeof(int));
    stack *stk = (stack*)malloc(sizeof(stack));
    if (stk == NULL) {
        free(array);
        return NULL;
    }
    if (size < 1) {
        fprintf(stderr, "Stack size has to be at least 1\n");
        free(array);
        free(stk); 
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
    stack *stk = new_stack(10);
    printf("HP-35 pocket calculator\n");
    int n = 10;
    char *buffer = malloc(n);
    bool run = true;
    while(run) {
        printf(" > ");
        fgets(buffer, n, stdin);
        if (strcmp(buffer, "\n") == 0) {
            run = false;
        } else if (strcmp(buffer, "+\n") == 0) {
            int a = pop(stk);
            int b = pop(stk);
            push(stk, a + b);
        }else if (strcmp(buffer, "-\n") == 0) {
            int a = pop(stk);
            int b = pop(stk);
            push(stk, b - a);

        } else if (strcmp(buffer, "*\n") == 0) {
            int a = pop(stk);
            int b = pop(stk);
            push(stk, a * b);
        } else if (strcmp(buffer, "/\n") == 0) {
            int a = pop(stk);
            int b = pop(stk);
            if (a == 0)
            {
                fprintf(stderr, "Cannot divide by 0\n");
                return 0;
            }
            else{
                push(stk, b / a);
            }

        } else {
            int val = atoi(buffer);
            push(stk, val);
        }
    }
    printf("the result is: %d\n\n", pop(stk));
    printf("I love reversed polish notation, don't you?\n");
}

