#include "../misc/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ROUND_COUNT     10000
#define BOREDOM_DIV     3

#define INIT_CAPACITY   4

#define STEP_STARTING   1
#define STEP_OP         2
#define STEP_TEST       3
#define STEP_TEST_TRUE  4
#define STEP_TEST_FALSE 5
#define N_MONKEY_LINES  7

//////////////////////////////// stack

typedef int* item_t;

typedef struct stack_t {
    item_t *arr;
    size_t size;
    size_t capacity;
} stack_t;

stack_t stack_new() {
    item_t *arr = malloc(INIT_CAPACITY * sizeof(item_t));
    stack_t retval = { arr, 0, INIT_CAPACITY };
    return retval;
}

void stack_push(stack_t *stack, item_t c) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stack->arr = realloc(stack->arr, stack->capacity * sizeof(item_t));
    }

    stack->arr[stack->size++] = c;
}

item_t stack_pop(stack_t *stack) {
    return stack->arr[--stack->size];
}

//////////////////////////////// monkey

typedef struct monkey {
    stack_t items;                  // list of items, implemented as a stack
    enum optype { ADD, MUL } op;    // type of operation performed by the monkey
    bool is_arg_old;                // is the old value the operation's 2nd argument?
    int arg2;                       // 2nd argument of the operation (unused if is_arg_old == true)
    int test_div;                   // divisor during testing
    int target_true;                // target monkey when test's result is true
    int target_false;               // target monkey when test's result is false
    int inspect_count;              // how many times the monkey inspected an item (result)
} monkey_t;

void do_op(monkey_t *monkeys, size_t n_monkeys, int m_id, item_t item) {
    monkey_t m = monkeys[m_id];

    for (int i = 0; i < n_monkeys; i++) {
        int arg2 = m.is_arg_old ? item[i] : m.arg2;

        if (m.op == ADD)
            item[i] += arg2;
        else
            item[i] *= arg2;

        item[i] %= monkeys[i].test_div;
    }

}

//////////////////////////////// solution

int main() {
    arrlen_t input = read_input("../day_11/input.txt");
    char delim[] = " \r\n";

    // find how many monkeys there are
    size_t n_monkeys = 0;

    for (int i = 0; i < input.len; i++) {
        char *line = input.arr[i];

        if (line[0] == 'M')
            n_monkeys++;
    }

    // parse the monkeys list
    monkey_t *monkeys = malloc(n_monkeys * sizeof(monkey_t));
    memset(monkeys, 0, n_monkeys * sizeof(monkey_t));

    for (int i = 0; i < n_monkeys; i++) {
        monkeys[i].items = stack_new();
    }

    for (int i = 0; i < input.len; i++) {
        char *line = input.arr[i];
        size_t monkey_id = i / N_MONKEY_LINES;
        size_t offset;

        switch (i % N_MONKEY_LINES) {
            case STEP_STARTING:
                strtok(line, delim); // "Starting"
                strtok(NULL, delim); // "items:"

                char *item_val = NULL;
                while ((item_val = strtok(NULL, ", \r\n")) != NULL) {
                    item_t item = malloc(n_monkeys * sizeof(int));
                    for (int j = 0; j < n_monkeys; j++)
                        item[j] = atoi(item_val);

                    stack_push(&monkeys[monkey_id].items, item);
                }

                break;

            case STEP_OP:
                strtok(line, delim); // "Operation:"
                strtok(NULL, delim); // "new"
                strtok(NULL, delim); // "="
                strtok(NULL, delim); // "old"

                char *op = strtok(NULL, delim);
                if (op[0] == '+')
                    monkeys[monkey_id].op = ADD;
                else
                    monkeys[monkey_id].op = MUL;

                char *arg = strtok(NULL, delim);
                if (strcmp(arg, "old") == 0)
                    monkeys[monkey_id].is_arg_old = true;
                else
                    monkeys[monkey_id].arg2 = atoi(arg);

                break;

            case STEP_TEST:
            case STEP_TEST_TRUE:
            case STEP_TEST_FALSE:
                offset = 0;
                while (!isdigit(line[offset]))
                    offset++;

                int val = atoi(line + offset);

                switch (i % N_MONKEY_LINES) {
                    case STEP_TEST:
                        monkeys[monkey_id].test_div = val;
                        break;

                    case STEP_TEST_TRUE:
                        monkeys[monkey_id].target_true = val;
                        break;

                    case STEP_TEST_FALSE:
                        monkeys[monkey_id].target_false = val;
                        break;
                }

                break;

            default:
                break;
        }
    }

    for (int i = 0; i < ROUND_COUNT; i++) {
        for (int m_id = 0; m_id < n_monkeys; m_id++) {
            monkey_t *m = &monkeys[m_id];

            while (m->items.size > 0) {
                item_t item = stack_pop(&m->items);
                do_op(monkeys, n_monkeys, m_id, item);

                int target = item[m_id] == 0 ? m->target_true : m->target_false;
                stack_push(&monkeys[target].items, item);

                m->inspect_count++;
            }
        }
    }

    long long max1 = 0, max2 = 0;

    for (int m_id = 0; m_id < n_monkeys; m_id++) {
        int n = monkeys[m_id].inspect_count;

        if (n > max1) {
            max2 = max1;
            max1 = n;

        } else if (n > max2) {
            max2 = n;
        }
    }

    printf("%lld", max1 * max2);

    free_input(input);
    return 0;
}