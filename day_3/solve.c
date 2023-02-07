#include "../misc/utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int get_prio(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 1;
    return c - 'A' + 27;
}

int main() {
    arrlen_t input = read_input("../day_3/input.txt");

    int result = 0;
    int items[53] = {0};

    for (int i = 0; i < input.len; i++) {
        char *line = input.arr[i];
        bool seen[53] = {0};
        size_t k = 0;

        while (line[k] != '\r' && line[k] != 0) {
            int prio = get_prio(line[k++]);

            if (!seen[prio]) {
                items[prio]++;
                seen[prio] = true;
            }
        }

        if (i % 3 == 2) {
            // this was the 3rd elf in a group
            for (int j = 52; j > 0; j--) {
                if (items[j] == 3) {
                    result += j;
                    printf("%d %d\n", i, j);
                }
            }

            for (int j = 0; j < 53; j++)
                items[j] = 0;
        }
    }

    printf("%d", result);

    free_input(input);
    return 0;
}