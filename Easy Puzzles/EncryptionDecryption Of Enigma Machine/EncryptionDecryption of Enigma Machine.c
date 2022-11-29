#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct {
    bool encode;
    int start_shift;
    char rotorsI[28];
    char rotorsII[28];
    char rotorsIII[28];
    char message[50];
} Reader;

void rotate(char* message, char* key, char* rotateTo)
{
    for (int i = 0; message[i]; ++i)
    {
        char* idx = strchr(key, message[i]);
        message[i] = rotateTo[idx-key];
    }
}

char doShift(char c, int shift, bool encode)
{
    c -= 65;
    c += shift * (encode ? 1 : -1);
    while (c >= 26) c -= 26;
    while (c < 0) c += 26;
    return c + 65;
}

void doRotates(Reader* read, bool encode)
{
    if (encode)
    {
        for (int i = 0; read->message[i]; ++i)
            read->message[i] = doShift(read->message[i], read->start_shift + i, encode);

        rotate(read->message, ALPHABET, read->rotorsI);
        rotate(read->message, ALPHABET, read->rotorsII);
        rotate(read->message, ALPHABET, read->rotorsIII);
    }
    else
    {
        rotate(read->message, read->rotorsIII, ALPHABET);
        rotate(read->message, read->rotorsII, ALPHABET);
        rotate(read->message, read->rotorsI, ALPHABET);

        for (int i = 0; read->message[i]; ++i)
            read->message[i] = doShift(read->message[i], read->start_shift + i, encode);
    }
}

int main()
{
    Reader* read = malloc(sizeof(Reader));

    char operation[7];
    scanf("%[^\n]", operation);fgetc(stdin);
    read->encode = strstr(operation, "ENCODE");

    int shift;
    scanf("%d", &shift); fgetc(stdin);
    read->start_shift = shift;

    scanf("%[^\n]", read->rotorsI); fgetc(stdin);
    scanf("%[^\n]", read->rotorsII); fgetc(stdin);
    scanf("%[^\n]", read->rotorsIII); fgetc(stdin);
    
    scanf("%[^\n]", read->message);

    doRotates(read, read->encode);

    printf("%s\n", read->message);
    return 0;
}
