#include "../misc/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>



int main() {
    arrlen_t input = read_input("../day_10/input.txt");

    int X = 1;
    int PC = 0;
    int clock = 1;

    bool ready = true;
    int addx_arg = 0;

    while (PC < input.len || !ready) {
        int crt_pos = (clock - 1) % 40;
        if (crt_pos - X >= -1 && crt_pos - X <= 1)
            printf("#");
        else
            printf(".");

        if (clock % 40 == 0 && clock <= 220)
            printf("\n");

        if (ready) { // can read next instr
            char *instr = strtok(input.arr[PC++], " \r\n");

            if (strcmp(instr, "addx") == 0) {
                addx_arg = atoi(strtok(NULL, " \r\n"));
                ready = false;
            }

        } else {
            X += addx_arg;
            ready = true;
        }

        clock++;
    }

    free_input(input);
    return 0;
}