#include "../misc/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ALPH_SIZE   26
#define WINDOW_SIZE 14

bool are_distinct(const int seen[]) {
    for (int i = 0; i < ALPH_SIZE; i++) {
        if (seen[i] > 1)
            return false;
    }

    return true;
}

int main() {
    arrlen_t input = read_input("../day_6/input.txt");

    char *signal = input.arr[0];
    size_t len = strlen(signal);
    int seen[ALPH_SIZE] = {0};

    for (int i = 0; i < WINDOW_SIZE; i++)
        seen[signal[i] - 'a']++;

    if (are_distinct(seen)) {
        printf("%d", WINDOW_SIZE);
        free_input(input);
        return 0;
    }

    for (int i = WINDOW_SIZE; i < len; i++) {
        seen[signal[i] - 'a']++;
        seen[signal[i - WINDOW_SIZE] - 'a']--;

        if (are_distinct(seen)) {
            printf("%d", i + 1);
            break;
        }
    }

    free_input(input);
    return 0;
}