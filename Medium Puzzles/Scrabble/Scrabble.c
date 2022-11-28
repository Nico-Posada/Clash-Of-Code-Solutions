#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// struct to store data
typedef struct
{
    char* word;
    int value;
} Results;

// get index of char in string
int indexOf(const char* letters, char c)
{
    char* result = strchr(letters, c);
    if (result == NULL) return -1;

    return (int)(result - letters);
}

// get score for scrabble word
int getValue(char* word)
{
    int len = strlen(word);
    const char* keys[] = {"eaionrtlsu", "dg", "bcmp", "fhvwy", "k", 0, 0, "jx", 0, "qz"};
    int result = 0;

    for (int c = 0; c < len; ++c)
    {
        for (int i = 0; i < 9; ++i)
        {
            if (!keys[i]) continue;
            
            if (indexOf(keys[i], word[c]) != -1)
            {
                result += i + 1;
                break;
            }
        }
    }

    return result;
}

// check if a word is a valid word given scrabble hand
bool isValid(const char* letters, char* word)
{
    char* dup = strdup(letters);
    int len = strlen(word);

    // word cant be greater than 7 chars
    if (len > 7)
        return false;

    for (int i = 0; i < len; ++i)
    {
        int idx = indexOf(dup, word[i]);
        if (idx == -1)
        {
            free(dup);
            return false;
        }

        // make sure to not reuse any letters
        dup[idx] = 0xFF; 
    }
    free(dup);
    return true;
}

// get value for given scrabble word
int check(const char* letters, char* word)
{
    if (!isValid(letters, word))
        return -1;

    return getValue(word);
}

int main()
{
    int N, i; scanf("%d", &N); fgetc(stdin);
    Results* words = calloc(N, sizeof(Results));

    for (i = 0; i < N; i++) {
        char* w = malloc(31);
        scanf("%[^\n]", w); fgetc(stdin);
        words[i].word = w;
    }

    char LETTERS[8];
    scanf("%[^\n]", LETTERS);

    // get all values for words
    for (i = 0; i < N; ++i)
    {
        words[i].value = check(LETTERS, words[i].word);
        if (words[i].value == -1)
            continue;
        fprintf(stderr, "%s -> %d\n", words[i].word, words[i].value);
    }

    // find index of word with largest score
    int idx = -1;
    int max = -1;

    for (i = 0; i < N; ++i)
    {
        if (words[i].value > max)
        {
            max = words[i].value;
            idx = i;
        }
    }

    // print result
    printf("%s\n", words[idx].word);

    // free memory
    for (i = 0; i < N; ++i) free(words[i].word);
    free(words);
    return 0;
}
