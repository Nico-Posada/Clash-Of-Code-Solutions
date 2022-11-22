#include <stdio.h>

int IntToChar(char val)
{
    return val + 48;
}

void BitShift(char* buf, char state, int count, int n)
{
    if (n<=count)
    {
        memset(buf, IntToChar(state=='H'), n);
    }
    else
    {
        memcpy(buf + count, buf, n - count);
        memset(buf, IntToChar(state=='H'), count);
    }
}

int main()
{
    char HL[2];
    char shifts[251];
    int n;
    scanf("%[^\n]", HL);
    scanf("%d", &n); fgetc(stdin);
    scanf("%[^\n]", shifts);

    char* bits = malloc(n);
    memset(bits, IntToChar(HL[0]=='H'), n);

    short* instructions = (short*)&shifts;

    while(*instructions)
    {
        char* instruction = (char*)(instructions++);
        char state = *instruction;
        int count = instruction[1]-48;

        BitShift(bits, state, count, n);
    }
    printf("%s\n", bits);

    free(bits);
    return 0;
}
