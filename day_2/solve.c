#include "../misc/utils.h"
#include <stdio.h>

int get_choice(int opp, int result) {
    if (result == 0) // loss
        return opp == 0 ? 2 : (opp - 1);
    if (result == 1) // draw
        return opp;
    return opp == 2 ? 0 : (opp + 1); // win
}

int main() {
    arrlen_t input = read_input("../day_2/input.txt");

    int result = 0;

    for (int i = 0; i < input.len; i++) {
        int opp = input.arr[i][0] - 'A';
        int game_result = input.arr[i][2] - 'X';
        result += get_choice(opp, game_result) + 1 + 3 * game_result;
    }

    printf("%d", result);

    free_input(input);
    return 0;
}