#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    int W, H;
    char start[512];
    char end[512];
    scanf("%d%d", &W, &H); fgetc(stdin);
    char** pic = calloc(H-2, sizeof(int*));

    scanf("%[^\n]", start); fgetc(stdin);
    for (int i = 0; i < H-2; ++i) {
        char* line = malloc(W);
        scanf("%[^\n]", line); fgetc(stdin);
        pic[i] = line;
    }
    scanf("%[^\n]", end); fgetc(stdin);

    int len = strlen(start);
    for (int i = 0; i < len; i += 3)
    {
        int x_idx = i;
        for (int y = 0; y < H-2; ++y)
        {
            if (x_idx > 0 && pic[y][x_idx-1] == '-')
                x_idx -= 3;
            else if (x_idx < W-1 && pic[y][x_idx+1] == '-')
                x_idx += 3;
        }
        printf("%c%c\n", start[i], end[x_idx]);
    }

    for (int i = 0; i < H-2; ++i) free(pic[i]);
    free(pic);
    return 0;
}
