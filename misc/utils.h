#ifndef AOC_2022_UTILS_H
#define AOC_2022_UTILS_H

#include <stdlib.h>

typedef struct arrlen_t {
    char **arr;
    size_t len;
} arrlen_t;

arrlen_t read_input(char *path);

void free_input(arrlen_t input);

#endif //AOC_2022_UTILS_H
