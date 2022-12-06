#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int getResult(char* board)
{
    int result = board[0];
    for (int i = 1; i < 9; ++i)
    {
        result <<= 1;
        result |= board[i];
    }
    return result;
}

void Booleanify(char* board)
{
    for (int i = 0; i < 9; ++i)
        board[i] = board[i] == '*';
}

void play(char* board, int num)
{
    // first item is array size bc C sucks at that
    // second item is the indexes that get inversed for the button that gets pressed
    int* changes[9] = {
        (int[]){4, 0,1,3,4},
        (int[]){3, 0,1,2},
        (int[]){4, 1,2,4,5},
        (int[]){3, 0,3,6},
        (int[]){5, 1,3,4,5,7},
        (int[]){3, 2,5,8},
        (int[]){4, 3,4,6,7},
        (int[]){3, 6,7,8},
        (int[]){4, 4,5,7,8},
    };

    int* selection = changes[num];
    for (int i = 1; i <= *selection; ++i)
        board[selection[i]] ^= 1;
}

int main()
{
    char board[9];
    scanf("%c %c %c", &board[0], &board[1], &board[2]);
    scanf(" %c %c %c", &board[3], &board[4], &board[5]);
    scanf(" %c %c %c", &board[6], &board[7], &board[8]);
    char all_buttons_pressed[101];
    scanf(" %[^\n]", all_buttons_pressed);

    Booleanify(board);

    for (int i = 0; all_buttons_pressed[i]; ++i)
        play(board, all_buttons_pressed[i]-49);

    char clone[9];
    for (int i = 0; i < 9; ++i)
    {
        memcpy(clone, board, 9);
        play(clone, i);
        if (getResult(clone) == 495)
        {
            printf("%d", i+1);
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}
