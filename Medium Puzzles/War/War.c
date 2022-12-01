#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VALUE 1000

bool shouldQuit = false;

typedef struct
{
    int* cards;
    int  war_deck[MAX_VALUE];
    int  war_deck_size;
} Player;

int get_card()
{
    char card[4];
    scanf("%s", card);

    switch (*card)
    {
        case '1': return 10;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
        default:  return -1;
    }
}

int deck_size(int* array)
{
    int count = 0;
    while (array[count]) count++;
    return count;
}

void arr_shift(int* array)
{
    int size = deck_size(array);
    for (int i = 1; i < size; ++i)
        array[i - 1] = array[i];
    array[size - 1] = 0;
}

int shift(int* cards)
{
    int result = cards[0];
    arr_shift(cards);
    return result;
}


bool can_play_war(int* cards)
{
    return deck_size(cards) >= 4;
}

void play_reg(int* p1, int* p2, int card_p1, int card_p2)
{
    if (card_p1 > card_p2)
    {
        int size = deck_size(p1);
        p1[size] = card_p1;
        p1[size+1] = card_p2;
    }
    else
    {
        int size = deck_size(p2);
        p2[size] = card_p1;
        p2[size+1] = card_p2;
    }
}

void append_winner(int* winner, Player* p1, Player* p2)
{
    int idx = deck_size(winner);
    for (int i = 0; i < p1->war_deck_size; ++i, ++idx)
        winner[idx] = p1->war_deck[i];

    for (int i = 0; i < p2->war_deck_size; ++i, ++idx)
        winner[idx] = p2->war_deck[i];

    memset(p1->war_deck, 0, p1->war_deck_size);
    memset(p2->war_deck, 0, p2->war_deck_size);
}

bool WAR(Player* p1, Player* p2)
{
    if (can_play_war(p1->cards) && can_play_war(p2->cards))
    {
        int p1_war_deck[3] = { shift(p1->cards), shift(p1->cards), shift(p1->cards) };
        int p2_war_deck[3] = { shift(p2->cards), shift(p2->cards), shift(p2->cards) };

        int p1_war_card = shift(p1->cards);
        int p2_war_card = shift(p2->cards);

        for (int i = 0; i < 3; ++i)
        {
            p1->war_deck[p1->war_deck_size + i] = p1_war_deck[i];
            p2->war_deck[p2->war_deck_size + i] = p2_war_deck[i];
        }

        p1->war_deck[p1->war_deck_size + 3] = p1_war_card;
        p2->war_deck[p2->war_deck_size + 3] = p2_war_card;

        p1->war_deck_size += 4;
        p2->war_deck_size += 4;

        if (p1_war_card == p2_war_card)
            return WAR(p1, p2);
        else
            return p1_war_card > p2_war_card;
    }
    else
    {
        printf("PAT\n");
        shouldQuit = true;
        return NULL;
    }
}

int main()
{
    int n, m, i;
    Player p1, p2;

    scanf("%d", &n);
    p1.cards = calloc(n + 1, sizeof(int));
    for (i = 0; i < n; ++i)
        p1.cards[i] = get_card();

    scanf("%d", &m);
    p2.cards = calloc(m + 1, sizeof(int));
    for (i = 0; i < m; ++i)
        p2.cards[i] = get_card();

    p1.cards = realloc(p1.cards, (m+n+1) * sizeof(int));
    p2.cards = realloc(p2.cards, (m+n+1) * sizeof(int));

    int rounds = 0;
    while (p1.cards[0] && p2.cards[0])
    {
        int card_p1 = shift(p1.cards);
        int card_p2 = shift(p2.cards);

        if (card_p1 == card_p2)
        {
            p1.war_deck[0] = card_p1;
            p2.war_deck[0] = card_p2;
            p1.war_deck_size = 1;
            p2.war_deck_size = 1;

            bool p1_wins = WAR(&p1, &p2);
            if (shouldQuit)
                return 0;

            if (p1_wins)
                append_winner(p1.cards, &p1, &p2);
            else
                append_winner(p2.cards, &p1, &p2);
        }
        else
            play_reg(p1.cards, p2.cards, card_p1, card_p2);

        ++rounds;
    }
    
    printf("%d %d", !p1.cards[0] + 1, rounds);
    free(p1.cards);
    free(p2.cards);
    
    return 0xDEADBEEF;
}
