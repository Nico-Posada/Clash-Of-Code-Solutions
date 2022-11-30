#include <stdio.h>
#include <math.h>

typedef struct
{
    char name;
    int x, y;
} Asteroid;

typedef struct
{
    Asteroid asteroid;
    float xPerUnit, yPerUnit;
} Asteroids;

int countAsteriods(char** pic, int height)
{
    int count = 0;
    for (int i = 0, j = 0; i < height; ++i, j = 0)
        while (pic[i][j])
            if (pic[i][j++] != '.')
                count++;
    return count;
}

int findIdxForRight(char name_left, Asteroid* right, int count)
{
    int i = 0;
    for (i = 0; i < count; ++i)
        if (name_left == right[i].name) 
            break;
    return i;
}

void fillData(Asteroids* ast, int count, char** pic_l, char** pic_r, int height, int t1, int t2)
{
    Asteroid* left = calloc(count, sizeof(Asteroid));
    Asteroid* right = calloc(count, sizeof(Asteroid));

    for (int y = 0, x = 0, i = 0, j = 0; y < height; ++y, x = 0)
    {
        while (pic_l[y][x] && pic_r[y][x])
        {
            if (pic_l[y][x] != '.')
            {
                left[i].name = pic_l[y][x];
                left[i].x = x;
                left[i].y = y;

                i++;
            }

            if (pic_r[y][x] != '.')
            {
                right[j].name = pic_r[y][x];
                right[j].x = x;
                right[j].y = y;

                j++;
            }
            x++;
        }
    }

    for (int i = 0; i < count; ++i)
    {
        int idx = findIdxForRight(left[i].name, right, count);
        ast[i].asteroid = left[i];
        int time = t2 - t1;
        ast[i].xPerUnit = (float)(right[idx].x - left[i].x) / (float)time;
        ast[i].yPerUnit = (float)(right[idx].y - left[i].y) / (float)time;
    }

    free(right);
    free(left);
}

// bubble sort bc i dont want to allocate any memory
// and i dont want to do somethin dumb like a quicksort
void reverseSort(Asteroids* ast, int size)
{
    Asteroids temp;
    int swaps = -1;

    while (swaps != 0)
    {   
        swaps = 0;
        for (int i = 1; i < size; ++i)
        {
            if (ast[i-1].asteroid.name < ast[i].asteroid.name)
            {
                temp = ast[i];
                ast[i] = ast[i-1];
                ast[i-1] = temp;
                swaps++;
            }
        }
    }
}

void clearPic(char** pic, int height)
{
    for (int i = 0, j = 0; i < height; ++i, j = 0)
        while(pic[i][j])
            pic[i][j++] = '.';
}

int main()
{
    int W, H, T1, T2, T3;
    scanf("%d%d%d%d%d", &W, &H, &T1, &T2, &T3);

    char** first_pic = calloc(H, sizeof(char*));
    char** second_pic = calloc(H, sizeof(char*));

    for (int i = 0; i < H; i++) {
        char* first_picture_row = malloc(W + 1);
        char* second_picture_row = malloc(W + 1);
        scanf("%s%s", first_picture_row, second_picture_row);
        first_pic[i] = first_picture_row;
        second_pic[i] = second_picture_row;
    }

    int asteroid_count = countAsteriods(first_pic, H);
    Asteroids* ast = calloc(asteroid_count, sizeof(Asteroids));
    fillData(ast, asteroid_count, first_pic, second_pic, H, T1, T2);

    reverseSort(ast, asteroid_count);
    clearPic(first_pic, H);

    for (int i = 0; i < asteroid_count; ++i)
    {
        fprintf(stderr, "Asteroid: %c\n--------------\nX/unit -> %f\nY/unit -> %f\nLeft X: %d\nLeft Y: %d\n\n", ast[i].asteroid.name, ast[i].xPerUnit, ast[i].yPerUnit, ast[i].asteroid.x, ast[i].asteroid.y);
        int time = T3 - T1;
        int new_x = floor(ast[i].xPerUnit * time) + ast[i].asteroid.x;
        int new_y = floor(ast[i].yPerUnit * time) + ast[i].asteroid.y;

        if ((new_x < 0 || W <= new_x) || (new_y < 0 || H <= new_y))
            continue;

        first_pic[new_y][new_x] = ast[i].asteroid.name;
    }

    for (int i = 0; i < H; ++i)
    {
        puts(first_pic[i]);
        free(first_pic[i]);
        free(second_pic[i]);
    }

    free(first_pic);
    free(second_pic);
    free(ast);
    return 0;
}
