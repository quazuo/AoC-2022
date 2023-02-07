#include "../misc/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    arrlen_t input = read_input("../day_8/input.txt");
    char **grid = input.arr;

    size_t width = strlen(input.arr[0]) - 2;
    size_t height = input.len;

    bool **visible = malloc(height * sizeof(bool *));
    for (int i = 0; i < height; i++) {
        visible[i] = malloc(width * sizeof(bool));
        memset(visible[i], 0, width);
    }

    int result = 0;

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int score = 1;
            int vec_x = 1, vec_y = 0;

            for (int i = 0; i < 4; i++) {
                int curr_score = 0;
                int xx = x, yy = y;

                do {
                    xx += vec_x;
                    yy += vec_y;
                    curr_score++;
                } while (xx > 0 && yy > 0 && xx < width - 1 && yy < height - 1
                        && grid[yy][xx] < grid[y][x]);

                if (x == 2 && y == 3) {
                    printf("(%d %d): %d\n", vec_x, vec_y, score);
                }

                score *= curr_score;

                // rotate the vector 90 deg c-clockwise
                int temp = vec_x;
                vec_x = -vec_y;
                vec_y = temp;
            }

            if (score > result)
                result = score;
        }
    }

    printf("%d", result);

    free_input(input);
    return 0;
}