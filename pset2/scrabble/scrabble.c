#include <ctype.h>
#include <stdio.h>
#include <string.h>

int score(char input[]);

int main(void)
{
    char word1[64];
    char word2[64];

    // Get word from both players
    printf("Player 1: ");
    scanf("%63s", word1);

    printf("Player 2: ");
    scanf("%63s", word2);

    // Get scores from both players
    int score1 = score(word1);
    int score2 = score(word2);

    // print output
    if (score1 > score2) 
    {
        printf("Player 1 wins!\n");
    } 
    else if (score1 < score2) 
    {
        printf("Player 2 wins!\n");
    }
    else 
    {
        printf("Tie!\n");
    }
}

int score(char input[]) 
{
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;

    for (int i = 0; i < strlen(input); i++) // to iterate through input
    { 
        for (int j = 0; j < strlen(alphabet); j++) // to iterale through alphabet
        {
            if (toupper(input[i]) == alphabet[j]) // if score match, add corresponding score. Note: input is capatilised
            {
                score += scores[j];
            }
        }
    }

    return score;
}