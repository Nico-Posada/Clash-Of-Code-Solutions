#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void fillSetValues(char* cmd, int* value)
{
    char* operation = strtok(cmd, " ");
    if (strcmp(operation, "VALUE"))
        return;

    char* strVal = strtok(NULL, " ");
    *value = atoi(strVal);
}

bool setValueIdx(char* cmd, int* values, int idx)
{
    int arg1, arg2;
    char* operation = strtok(cmd, " ");
    char* a1 = strtok(NULL, " ");
    char* a2 = strtok(NULL, " ");
    bool isVALUE = !strcmp(operation, "VALUE");

    if (isVALUE && a1[0] != '$') return true;
    bool isA1 = a1[0] == '$';
    int a1V = atoi(a1 + isA1);
    arg1 = isA1 ? values[a1V] : a1V;

    if (isVALUE)
    {
        values[idx] = arg1;
        return true;
    }

    bool isA2 = (a2[0] == '$');
    int a2V = atoi(a2 + isA2);
    arg2 = isA2 ? values[a2V] : a2V;
    if (arg1 == 2139062143 || arg2 == 2139062143) return false;

    switch (operation[0])
    {
        case 'A':
            values[idx] = arg1 + arg2;
            break;
        case 'S':
            values[idx] = arg1 - arg2;
            break;
        case 'M':
            values[idx] = arg1 * arg2;
            break;
        default:
            break;
    }
    return true;
}

int main()
{
    int cmdCount, len;
    char** commands;
    int* values;
    char opBuf[6];
    char a1Buf[7];
    char a2Buf[7];
    scanf("%d", &cmdCount);

    commands = calloc(cmdCount, sizeof(char*));
    values = calloc(cmdCount, sizeof(int));
    // sets all values to 0x7f, just a random default value
    memset(values, 0x7F, cmdCount * sizeof(int));
    
    for (int i = 0; i < cmdCount; i++) {
        scanf("%s%s%s", opBuf, a1Buf, a2Buf);
        commands[i] = (char*)malloc(20);
        sprintf(commands[i], "%s %s %s", opBuf, a1Buf, a2Buf);
    }

    // fill in all predetermined values
    for (int i = 0; i < cmdCount; ++i)
    {
        char* temp = strdup(commands[i]);
        fillSetValues(temp, &values[i]);
        free(temp);
    }

    // write values
    bool shouldBreak = false;
    while (!shouldBreak)
    {
        shouldBreak = true;
        for (int i = 0; i < cmdCount; ++i)
        {
            char* str = strdup(commands[i]);
            if (!setValueIdx(str, values, i))
                shouldBreak = false;
            free(str);
        }
    }

    // print values and also free memory
    for (int i = 0; i < cmdCount; ++i)
    {
        printf("%d\n", values[i]);
        free(commands[i]);
    }
    free(commands);
    return 0;
}
