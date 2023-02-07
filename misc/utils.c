#include "utils.h"

#include <stdio.h>

arrlen_t read_input(char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp)
        perror("No input file");

    size_t len = 0, capacity = 4;
    char **input = malloc(capacity * sizeof(char *));
    char *buf = NULL;
    size_t line_len;

    while (getline(&buf, &line_len, fp) != -1) {
        if (len == capacity) {
            capacity *= 2;
            input = realloc(input, capacity * sizeof(char *));
        }

        input[len++] = buf;
        buf = NULL;
    }

    free(buf); // need to free the last one
    fclose(fp);

    arrlen_t retval = {input, len};
    return retval;
}

void free_input(arrlen_t input) {
    for (int i = 0; i < input.len; i++) {
        free(input.arr[i]);
    }

    free(input.arr);
}

