#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum Letter {
    LP_AB,
    LP_FG
};

typedef struct {
    char ab[2];
    int cde;
    char fg[2];
} LicensePlate;

void addLetter(LicensePlate* license, enum Letter letter)
{
    char Letters[3];
    strncpy(Letters, letter == LP_AB ? license->ab : license->fg, 2);

    Letters[1]++;
    if (Letters[1] == 91)
    {
        Letters[1] = 'A';
        Letters[0]++;
        if (Letters[0] == 91)
            Letters[0] = 'A';
    }

    strncpy(letter == LP_AB ? license->ab : license->fg, Letters, 2);
}

void solve(int n, LicensePlate* license)
{
    for (int i = 0; i < n; ++i)
    {
        license->cde++;
        if (license->cde < 1000) continue;

        license->cde = 1;
        addLetter(license, LP_FG);

        if (strcmp(license->fg, "AA")) continue;

        addLetter(license, LP_AB);
    }
}

int main()
{
    LicensePlate lp;
    int n;
    scanf("%c%c-%03d-%c%c", &lp.ab[0], &lp.ab[1], &lp.cde, &lp.fg[0], &lp.fg[1]);
    scanf("%d", &n);
    solve(n, &lp);
    printf("%s-%03d-%s\n", lp.ab, lp.cde, lp.fg);

    return 0;
}
