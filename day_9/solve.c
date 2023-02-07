#include "../misc/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INIT_CAPACITY   4
#define N_KNOTS         10

typedef struct pos {
    int x;
    int y;
} pos_t;

pos_t get_vec(char dir) {
    pos_t vec = {0, 0};

    switch (dir) {
        case 'U': vec.x = 0; vec.y = 1; break;
        case 'R': vec.x = 1; vec.y = 0; break;
        case 'D': vec.x = 0; vec.y = -1; break;
        case 'L': vec.x = -1; vec.y = 0; break;
        default: perror("Invalid direction");
    }

    return vec;
}

void normalize_rope(pos_t *head, pos_t *tail) {
    int dist_x = head->x - tail->x;
    int dist_y = head->y - tail->y;

    if (dist_x >= -1 && dist_x <= 1 && dist_y >= -1 && dist_y <= 1)
        return;

    if (dist_x == 2 || dist_x == -2) {
        tail->x += dist_x / 2;
        if (dist_y > 0)
            tail->y += 1;
        else if (dist_y < 0)
            tail->y += -1;

    } else if (dist_y == 2 || dist_y == -2) {
        tail->y += dist_y / 2;
        if (dist_x > 0)
            tail->x += 1;
        else if (dist_x < 0)
            tail->x += -1;
    }
}

int main() {
    arrlen_t input = read_input("../day_9/input.txt");

    pos_t rope[N_KNOTS];
    memset(rope, 0, N_KNOTS * sizeof(pos_t));

    // i dont feel like coding a set...
    size_t capacity = INIT_CAPACITY;
    size_t n_seen = 1;
    pos_t *seen = malloc(capacity * sizeof(pos_t));
    seen[0] = rope[0]; // (0, 0) is always visited

    for (int i = 0; i < input.len; i++) {
        char *line = input.arr[i];

        char dir = strtok(line, " \r\n")[0];
        pos_t vec = get_vec(dir);

        int steps = atoi(strtok(NULL, " \r\n"));

        for (int j = 0; j < steps; j++) {
            rope[0].x += vec.x;
            rope[0].y += vec.y;

            for (int k = 1; k < N_KNOTS; k++) {
                normalize_rope(&rope[k - 1], &rope[k]);
            }

            bool was_seen = false;
            for (int k = 0; k < n_seen && !was_seen; k++) {
                pos_t p = seen[k];
                pos_t tail = rope[N_KNOTS - 1];

                if (p.x == tail.x && p.y == tail.y)
                    was_seen = true;
            }

            if (!was_seen) {
                if (n_seen == capacity) {
                    capacity *= 2;
                    seen = realloc(seen, capacity * sizeof(pos_t));
                }

                seen[n_seen++] = rope[N_KNOTS - 1];
            }
        }
    }

    printf("%zu", n_seen);

    free_input(input);
    return 0;
}