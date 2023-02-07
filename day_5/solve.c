#include "../misc/utils.h"
#include <stdio.h>
#include <string.h>

#define INIT_CAPACITY 4

typedef struct stack_t {
    char *arr;
    size_t size;
    size_t capacity;
} stack_t;

stack_t stack_new() {
    char *arr = malloc(INIT_CAPACITY * sizeof(char));
    stack_t retval = { arr, 0, INIT_CAPACITY };
    return retval;
}

void stack_push(stack_t *stack, char c) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stack->arr = realloc(stack->arr, stack->capacity * sizeof(char));
    }

    stack->arr[stack->size++] = c;
}

char stack_pop(stack_t *stack) {
    return stack->arr[--stack->size];
}

int main() {
    arrlen_t input = read_input("../day_5/input.txt");

    // find how many stacks there are
    int i = 0;
    while (input.arr[i][0] != '\r')
        i++;
    i--;

    size_t n_stacks = strlen(input.arr[i]) / 4;

    // init stacks
    stack_t *stacks = malloc(n_stacks * sizeof(stack_t));
    for (int j = 0; j < n_stacks; j++) {
        stacks[j] = stack_new();
    }

    // fill stacks
    while (--i >= 0) {
        char *line = input.arr[i];

        for (int j = 0; j < n_stacks; j++) {
            if (line[4 * j + 1] != ' ') {
                stack_push(&stacks[j], line[4 * j + 1]);
            }
        }
    }

    // go to first 'move' instruction
    i = 0;
    while (input.arr[i][0] != 'm')
        i++;

    // execute 'move' instructions
    stack_t temp = stack_new();

    for (; i < input.len; i++) {
        char *line = input.arr[i];
        int n, from, to;

        sscanf(line, "move %d from %d to %d", &n, &from, &to);

        for (int j = 0; j < n && stacks[from - 1].size > 0; j++) {
            stack_push(&temp, stack_pop(&stacks[from - 1]));
        }

        while (temp.size > 0) {
            stack_push(&stacks[to - 1], stack_pop(&temp));
        }
    }

    for (int j = 0; j < n_stacks; j++) {
        char pop = stacks[j].size == 0 ? ' ' : stack_pop(&stacks[j]);
        printf("%c", pop);
    }

    free(temp.arr);
    for (int j = 0; j < n_stacks; j++)
        free(stacks[j].arr);
    free(stacks);
    free_input(input);
    return 0;
}