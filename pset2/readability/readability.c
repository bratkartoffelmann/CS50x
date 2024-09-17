#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int coleman_liau_index(float L, float S);
int count_letters(char input[]);
int count_words(char input[]);
int count_sentences(char input[]);

int main(void)
{
    char text[1024];

    // get text inputs
    printf("Text: ");
    fgets(text, sizeof(text), stdin);
    
    // calculate Coleman-Liau index
    int letter_cnt = count_letters(text);
    int word_cnt = count_words(text);
    int sentence_cnt = count_sentences(text);
    float L = letter_cnt / ((float)word_cnt/100);
    float S = sentence_cnt / ((float)word_cnt/100);
    int index = coleman_liau_index(L, S);

    // output
    if (index < 1) 
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16) 
    {
        printf("Grade 16+\n");
    }
    else 
    {
        printf("Grade %i\n", index);
    }
}



int coleman_liau_index(float L, float S)
{
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return round(index);
}

int count_letters(char input[]) 
{
    int letters = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        if (isalpha(input[i])) 
        {
            letters++;
        }
    }
    return letters;
}

int count_words(char input[])
{
    int words = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        if (isspace((unsigned char)input[i])) 
        {
            words++;
        }
    }
    return words;
}

int count_sentences(char input[])
{
    int sentences = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '.' || input[i] == '?' || input[i] == '!') 
        {
            sentences++;
        }
    }
    return sentences;
}