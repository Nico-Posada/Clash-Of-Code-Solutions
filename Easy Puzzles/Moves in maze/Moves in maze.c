#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 1000

typedef struct {
    int x,y;
} Point;

typedef struct {
    Point pt;
    int idx;
} Stack;

int h,w,shifted=0,size;
char chars[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
static Point directions[4] = {
    1,0,
    0,1,
    -1,0,
    0,-1
};

int main()
{
    int sx, sy;
    scanf("%d%d", &w, &h); fgetc(stdin);
    char** grid = calloc(h, sizeof(char*));

    for (int i = 0; i < h; i++) {
        char* line = malloc(w);
        scanf("%[^\n]", line); fgetc(stdin);

        for (int j = 0; j < w; ++j) {
            if (line[j] == 'S') {
                sx = j;
                sy = i;
                line[j] = '.';
            }
        }

        grid[i] = line;
    }

    Stack* to_search = calloc(STACK_SIZE, sizeof(Stack));
    to_search[0].pt.x = sx; to_search[0].pt.y = sy; to_search[0].idx = 0;

    int size = 1;
    while (size > 0) {
        // pop the bottom item queue style
        int sx = to_search[0].pt.x, sy = to_search[0].pt.y, idx = to_search[0].idx;
        size--; shifted++; to_search++;

        if (grid[sy][sx] != '.')
            continue;

        grid[sy][sx] = chars[idx];
        for (int i = 0; i < 4; ++i) {
            int nx = (directions[i].x + sx) % w, ny = (directions[i].y + sy) % h;
            if (nx < 0) nx += w;
            if (ny < 0) ny += h;

            if (grid[ny][nx] != '.')
                continue;

            to_search[size].pt.x = nx;
            to_search[size].pt.y = ny;
            to_search[size].idx = idx+1;
            size++;            
        }
    }

    for (int i = 0; i < h; ++i) {
        puts(grid[i]);
        free(grid[i]);
    }

    free(grid);
    free(to_search - shifted);
    return 0;
}
