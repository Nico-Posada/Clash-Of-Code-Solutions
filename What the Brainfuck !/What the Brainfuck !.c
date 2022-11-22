#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isValidChar(char c)
{
    char chars[] = "><+-.,[]";
    for (int i = 0; i < 9; ++i)
    {
        if (chars[i] == c)
            return true;
    }
    return false;
}

bool checkSyntax(char* commands)
{
    int len = strlen(commands), count = 0;
    for (int i = 0; i < len; ++i)
    {
        if (commands[i] == '[')
            count += 1;
        else if (commands[i] == ']')
            count -= 1;
        
        if (count < 0)
        {
            puts("SYNTAX ERROR");
            return false;
        }
    }

    if (count != 0)
    {
        puts("SYNTAX ERROR");
        return false;
    }
    return true;
}

void jmp(int* idx, char* commands, bool forward)
{
    int toSkip = 0;
    if (forward)
    {
        ++*idx;
        while (1)
        {
            if (commands[*idx] == '[') 
                toSkip++;
            else if (commands[*idx] == ']')
            {
                if (toSkip == 0)
                    return;
                else
                    toSkip--;
            }

            ++*idx;
        }
    }
    else
    {   
        --*idx;
        while(1)
        {
            if (commands[*idx] == ']')
                toSkip++;
            else if (commands[*idx] == '[')
            {
                if (toSkip == 0)
                    return;
                else
                    toSkip--;
            }
            
            --*idx;
        }
    }
}

void getCode(char* line_input, char* buffer)
{
    memset(buffer, 0, 512);
    int len = strlen(line_input);
    for (int i = 0; i < len; ++i)
    {
        if (isValidChar(line_input[i]))
            strncat(buffer, line_input + i, 1);
    }
}

int main()
{
    int L, S, N, i, c;
    char* commands = malloc(999);
    scanf("%d%d%d", &L, &S, &N); fgetc(stdin);

    char* temp_buffer = malloc(512);
    for (i = 0; i < L; i++) {
        char r[512]; // increase if validators fail
        scanf("%[^\n]", r); fgetc(stdin);
        getCode(r, temp_buffer);
        strcat(commands, temp_buffer);
    }
    free(temp_buffer);

    int commandLen = strlen(commands);

    // SYNTAX ERROR CHECK
    if (!checkSyntax(commands))
        return 0;

    int* cells = calloc(S, sizeof(int));

    int ptr = 0;
    int idx = 0;

    while(1)
    {
        char command = commands[idx];
        switch(command)
        {
            case '>':
                ptr += 1;
                break;
            case '<':
                ptr -= 1;
                break;
            case '+':
                cells[ptr] += 1;
                break;
            case '-':
                cells[ptr] -= 1;
                break;
            case '.':
                printf("%c", cells[ptr]);
                break;
            case ',':
                scanf("%d", &c);
                cells[ptr] = c;
                break;
            case '[':
                if (!cells[ptr]) jmp(&idx, commands, true);
                break;
            case ']':
                if (cells[ptr]) jmp(&idx, commands, false);
                break;
            default:
                break;
        }

        if (ptr == S || ptr == -1)
        {
            puts("POINTER OUT OF BOUNDS");
            return 0;
        }
        else if (cells[ptr] < 0 || cells[ptr] > 255)
        {
            puts("INCORRECT VALUE");
            return 0;
        }
        
        idx += 1;
        if (idx >= commandLen)
            break;
    }

    free(commands);
    free(cells);
    return 0;
}
