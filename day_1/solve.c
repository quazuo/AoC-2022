#include "../misc/utils.h"
#include <stdio.h>

int main() {
    arrlen_t input = read_input("../day_1/input.txt");

    int top1 = 0, top2 = 0, top3 = 0;
    int curr_sum = 0;

    for (int i = 0; i < input.len; i++) {
        if (input.arr[i][0] == '\n' || input.arr[i][0] == '\r') {
            if (curr_sum > top1) {
                top3 = top2;
                top2 = top1;
                top1 = curr_sum;
            }
            else if (curr_sum > top2) {
                top3 = top2;
                top2 = curr_sum;
            }
            else if (curr_sum > top3) {
                top3 = curr_sum;
            }

            curr_sum = 0;
        } else {
            curr_sum += atoi(input.arr[i]);
        }
    }

    printf("%d", top1 + top2 + top3);

    free_input(input);
    return 0;
}