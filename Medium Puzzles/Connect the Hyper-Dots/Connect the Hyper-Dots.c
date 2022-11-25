#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct _Reader
{
    char letter;
    int* points;
} Reader;

bool hasCrossed(int* start, int* points, int dimensions)
{
    for (int i = 0; i < dimensions; ++i)
        if (start[i] * points[i] < 0) return true;
    return false;
}

bool shouldSkip(int* toSkip, int idx, int size)
{
    for (int i = 0; i < size; ++i)
        if (toSkip[i] == idx) return true;
    return false;
}

double getDist(int* start, int* points, int dimensions)
{
    double sum = 0;
    for (int i = 0; i < dimensions; ++i)
        sum += pow(start[i] - points[i], 2);
    return sqrt(sum);
}

int main()
{
    int count, dimensions;
    scanf("%d%d", &count, &dimensions); fgetc(stdin);

    Reader* read = calloc(count, sizeof(Reader));

    for (int i = 0; i < count; i++) {
        int* dims = calloc(dimensions, sizeof(int));
        scanf("%c", &read[i].letter); 
        for (int j = 0; j < dimensions; ++j) scanf("%d", &dims[j]);
        fgetc(stdin);

        read[i].points = dims;
    }

    int size = count * sizeof(int);
    int* toSkip = malloc(size);
    memset(toSkip, 0xFF, size);
    int toSkipIdx = 0;

    int* basePoint = calloc(dimensions, sizeof(int));

    while (toSkipIdx != count)
    {
        double min = 0xDEADBEEF;
        int idx = 0;
        for (int i = 0; i < count; ++i)
        {
            if (shouldSkip(toSkip, i, count)) continue;

            double d = getDist(basePoint, read[i].points, dimensions);
            if (d < min)
            {
                min = d;
                idx = i;
            }
        }

        if (hasCrossed(basePoint, read[idx].points, dimensions))
            printf(" ");
        
        basePoint = read[idx].points;
        printf("%c", read[idx].letter);
        toSkip[toSkipIdx++] = idx;
    }
    
    for (int i = 0; i < count; ++i) free(read[i].points);
    free(read);
    free(toSkip);
    return 0;
}
