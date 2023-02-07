#include "../misc/utils.h"
#include <stdio.h>
#include <string.h>

int main() {
    arrlen_t input = read_input("../day_4/input.txt");

    int result = 0;

    for (int i = 0; i < input.len; i++) {
        char *line = input.arr[i];

        char *range_1 = strtok(line, ",");
        char *range_2 = strtok(NULL, ",");

        int left_1 = atoi(strtok(range_1, "-"));
        int right_1 = atoi(strtok(NULL, "-"));

        int left_2 = atoi(strtok(range_2, "-"));
        int right_2 = atoi(strtok(NULL, "-"));

        if (!(right_2 < left_1 || left_2 > right_1))
            result++;
    }

    printf("%d", result);

    free_input(input);
    return 0;
}