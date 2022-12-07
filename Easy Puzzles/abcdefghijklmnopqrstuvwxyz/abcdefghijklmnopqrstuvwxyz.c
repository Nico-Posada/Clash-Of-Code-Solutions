#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char letter;
    int x, y;
    struct Point_t* next;
} Point_t;

bool scan(Point_t* pt, char** pic, int n)
{
    if (pt->letter == 'z') return true;

    // this is probably not very memory safe but the way it works is cool so idc
    Point_t* new_pt = malloc(sizeof(Point_t));

    int change_x = 0, change_y = 0;

    char search = pt->letter + 1;
    if (0 < pt->x && pic[pt->y][pt->x-1] == search)
        change_x = -1;
    else if (n-1 > pt->x && pic[pt->y][pt->x+1] == search)
        change_x = 1;
    else if (0 < pt->y && pic[pt->y-1][pt->x] == search)
        change_y = -1;
    else if (n-1 > pt->y && pic[pt->y+1][pt->x] == search)
        change_y = 1;
    else return false;

    new_pt->letter = search;
    new_pt->x = pt->x + change_x;
    new_pt->y = pt->y + change_y;
    pt->next = (struct Point_t*)new_pt;

    return scan(new_pt, pic, n);
}

void findA(Point_t* pt, char** pic, int n)
{
    for (int y = 0; y < n; ++y)
        for (int x = 0; x < n; ++x)
            if (pic[y][x] == 'a')
            {
                pt->letter = 'a';
                pt->x = x;
                pt->y = y;

                if (scan(pt, pic, n))
                    return;
            }
}

int main()
{
    int n;
    Point_t point;
    scanf("%d", &n);

    char** pic = calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
        char* line = malloc(n+1);
        scanf("%s", line);
        pic[i] = line;
    }

    findA(&point, (char**)pic, n);
    
    // make picture all dashes
    for (int y = 0; y < n; ++y)
        for (int x = 0; x < n; ++x)
            pic[y][x] = '-';

    Point_t* pt = &point;
    while (pt)
    {
        pic[pt->y][pt->x] = pt->letter;
        pt = (Point_t*)pt->next;
    }

    for (int i = 0; i < n; ++i)
    {
        puts(pic[i]);
        free(pic[i]);
    }

    free(pic);
    return 0;
}
