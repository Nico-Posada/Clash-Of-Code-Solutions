#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

double distance(x1, y1, x2, y2)
{
    return sqrt( pow(y2-y1, 2) + pow(x2-x1, 2) );
}

int main()
{
    char instructions[501];
    scanf("%[^\n]", instructions);

    char* field[25];
    // fill with TRUE values
    char* str = "\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01";
    for (int i = 0; i < 25; ++i)
        field[i] = strdup(str);

    char* ins = strtok(instructions, " ");

    int col, row, extra;
    double radius;

    while (ins)
    {
        if (*ins != 'P') // regular instruction
            extra = 0;
        else if (ins[5] == 'M') // PRINTMOW
        {
            ins += 8;
            extra = 1;
        }
        else // PRINT
        {
            ins += 5;
            extra = 2;
        }

        col = *ins - 97;
        row = ins[1] - 97;
        radius = atoi(ins + 2)/2.f;

        for (int y = 0; y < 25; ++y)
        {
            for (int x = 0; x < 19; ++x)
            {
                if (radius >= distance(x, y, col, row))
                {
                    if (!extra)
                        field[y][x] = false;
                    else if (extra == 1)
                        field[y][x] ^= true;
                    else
                        field[y][x] = true;
                }
            }
        }

        ins = strtok(NULL, " ");
    }

    for (int y = 0; y < 25; ++y)
    {
        for (int x = 0; x < 19; ++x)
            printf("%s", field[y][x] ? "{}" : "  ");

        printf("\n");
        free(field[y]);
    }

    return 0;
}
