#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkPalindrome(char* str)
{
    int len = strlen(str);
    for (int i = 0; i < len/2; ++i)
        if (str[i] ^ str[len-i-1])
            return false;

    return true;
}

int main()
{
    int n;
    char* result = malloc(n*2+1);
    scanf("%d", &n); fgetc(stdin);
    scanf("%[^\n]", result);
    int idx = 0;

    while (idx < n)
    {
        if (checkPalindrome(result))
            break;
        
        memcpy(result + n + 1, result + n, ++idx);
        result[n] = result[idx-1];
    }

    printf("%d\n", idx);
    free(result);
    return 0;
}
