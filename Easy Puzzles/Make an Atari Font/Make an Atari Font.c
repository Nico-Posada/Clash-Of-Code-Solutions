#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define ull unsigned long long

void rstrip(char* str)
{
    int len = strlen(str);
    for (int i = len - 1; i >= 0; --i)
    {
        if (str[i] != ' ') return;
        str[i] = 0;
    }
}

int main()
{
    char a_word[17];
    char buffer[999] = {0};

    ull map[] = {0x1818243C42420000, 0x7844784444780000, 0x3844808044380000, 
                0x7844444444780000, 0x7C407840407C0000, 0x7C40784040400000, 
                0x3844809C44380000, 0x42427E4242420000, 0x3E080808083E0000, 
                0x1C04040444380000, 0x4448507048440000, 0x40404040407E0000, 
                0x4163554941410000, 0x4262524A46420000, 0x1C222222221C0000, 
                0x7844784040400000, 0x1C222222221C0200, 0x7844785048440000, 
                0x1C22100C221C0000, 0x7F08080808080000, 0x42424242423C0000, 
                0x8142422424180000, 0x4141495563410000, 0x4224181824420000, 
                0x4122140808080000, 0x7E040810207E0000};

    scanf("%[^\n]", a_word);
    for (int line = 0; line < 8; ++line)
    {
        int idx = 0;
        for (int i = 0; a_word[i]; ++i)
        {
            ull bits = map[a_word[i] - 'A'];
            

            for (int a = line * 8 + 1; a <= (line + 1) * 8; ++a)
            {
                char c = bits >> (64 - a) & 1 ? 'X' : ' ';
                buffer[idx++] = c;
            }
        }

        rstrip(buffer);
        if (*buffer)
            printf("%s\n", buffer);
        memset(buffer, 0, 999);
    }

    return 0;
}
