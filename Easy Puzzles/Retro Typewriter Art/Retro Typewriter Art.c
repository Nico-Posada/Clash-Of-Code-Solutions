#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int count;
    char c;
} cmd;

void getCmd(cmd* cmd, char* token, bool lengthIs2)
{
    char temp[8];
    int len = strlen(token);
    cmd->c = token[len - 1];
    strncpy(temp, token, len-1-lengthIs2);
    cmd->count = atoi(temp);
}

char* checkQuirks(char* token)
{
    char* result;

    result = strstr(token, "sp");
    if (result != NULL) return "sp";
    result = strstr(token, "bS");
    if (result != NULL) return "bS";
    result = strstr(token, "sQ");
    if (result != NULL) return "sQ";
    result = strstr(token, "nl");
    if (result != NULL) return "nl";
    return NULL;
}



int main()
{
    char T[1001];
    char* print;
    cmd command;
    scanf("%[^\n]", T);

    char* token = strtok(T, " ");
    while (token != NULL)
    {
        char* result = checkQuirks(token);
        int count;
        char c;

        if (result != NULL)
        {
            if (!strcmp(result, "sp")) c = ' ';
            else if (!strcmp(result, "bS")) c = '\\';
            else if (!strcmp(result, "sQ")) c = '\'';
            else if (!strcmp(result, "nl")) c = '\n';
            else fprintf(stderr, "ERROR FINDING MATCH -> %s\n", result);
            getCmd(&command, token, true);
            count = c == '\n' ? 1 : command.count;
        }
        else
        {
            getCmd(&command, token, false);
            c = command.c;
            count = command.count;
        }

        print = malloc(count);
        memset(print, c, count);
        printf("%s", print);
        token = strtok(NULL, " ");
    }

    free(print);
    return 0;
}
