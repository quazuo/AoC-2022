#include "../misc/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INIT_CAPACITY   4
#define SIZE_CAP        100000
#define TOTAL_MEMORY    70000000
#define UPDATE_SIZE     30000000

struct vector_t;

struct vector_t *vec_new();

typedef struct node {
    char *name;
    long long int size;
    struct vector_t *children;
    struct node *parent;
} node_t;

node_t *make_node(const char *name, int size, node_t *parent) {
    node_t *retval = malloc(sizeof(node_t));

    node_t node = { name, size, vec_new(), parent };
    *retval = node;

    return retval;
}

typedef struct vector_t {
    node_t **arr;
    size_t size;
    size_t capacity;
} vector_t;

vector_t *vec_new() {
    node_t **arr = malloc(INIT_CAPACITY * sizeof(node_t *));
    vector_t *retval = malloc(sizeof(vector_t));

    retval->arr = arr;
    retval->size = 0;
    retval->capacity = INIT_CAPACITY;

    return retval;
}

void vec_add(vector_t *vec, node_t *node) {
    vec->arr[vec->size++] = node;

    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->arr = realloc(vec->arr, vec->capacity * sizeof(node_t *));
    }
};

node_t *vec_find(vector_t *vec, char *key) {
    for (int i = 0; i < vec->size; i++) {
        if (strcmp(vec->arr[i]->name, key) == 0)
            return vec->arr[i];
    }

    return NULL;
}

node_t *get_child(node_t *node, char *name) {
    node_t *res = vec_find(node->children, name);

    if (res)
        return res;

    res = make_node(name, -1, node);
    vec_add(node->children, res);
    return res;
}

long long int calc_dir_sizes(node_t *node) {
    if (node == NULL)
        return 0;
    if (node->size != -1)
        return node->size;

    long long int size = 0;

    for (int i = 0; i < node->children->size; i++) {
        size += calc_dir_sizes(node->children->arr[i]);
    }

    node->size = size;
    return size;
}

void find_result(node_t *node, long long *result, long long needed) {
    if (node == NULL)
        return;

    if (node->children->size > 0 && node->size >= needed && node->size < *result)
        *result = node->size;

    for (int i = 0; i < node->children->size; i++)
        find_result(node->children->arr[i], result, needed);
}

int main() {
    arrlen_t input = read_input("../day_7/input.txt");
    char delim[] = " \r\n";

    node_t *root = make_node("/", -1, NULL);
    root->parent = root;

    node_t *curr_node = root;

    for (int i = 0; i < input.len; i++) {
        char *line = input.arr[i];
        char *fst = strtok(line, delim);
        char *name = strtok(NULL, delim);

        if (strcmp(fst, "$") == 0) { // user command
            if (strcmp(name, "ls") == 0)
                continue;

            // executing 'cd'
            char *cd_arg = strtok(NULL, delim);

            if (strcmp(cd_arg, "..") == 0)      // go back one level
                curr_node = curr_node->parent;
            else if (strcmp(cd_arg, "/") == 0)  // go to root
                curr_node = root;
            else                                // go to child
                curr_node = get_child(curr_node, cd_arg);

        } else { // 'ls' result
            node_t *child = get_child(curr_node, name);

            if (strcmp(fst, "dir") != 0) { // not looking at a directory
                child->size = strtol(fst, NULL, 10);
            }
        }
    }

    calc_dir_sizes(root);

    long long disk_space = TOTAL_MEMORY - root->size;

    if (disk_space >= UPDATE_SIZE) {
        printf("0");

    } else {
        long long needed = UPDATE_SIZE - disk_space;
        long long result = TOTAL_MEMORY; // whatever, just a big value
        find_result(root, &result, needed);
        printf("%lld", result);
    }

    free_input(input);
    return 0;
}