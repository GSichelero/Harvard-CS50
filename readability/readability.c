#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_letters(string text);
int count_spaces(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    printf("\n");


    float letters_num = count_letters(text);
    printf("%.0f letter(s)\n", letters_num);

    float words_num = count_spaces(text) + 1;
    printf("%.0f word(s)\n", words_num);

    float sentences_num = count_sentences(text);
    printf("%.0f sentence(s)\n", sentences_num);

    float letters_per_100_word = letters_num / (words_num / 100);
    float sentences_per_100_word = sentences_num / (words_num / 100);
    float index = (0.0588 * letters_per_100_word) - (0.296 * sentences_per_100_word) - 15.8;

    if (index <= 0.5)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 15.5)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}



int count_letters(string text)
{
    int letters_count = 0;

    for (int index = 0, text_len = strlen(text); index < text_len; index++)
    {
        if (text[index] >= 'A' && text[index] <= 'z')
        {
            letters_count++;
        }
    }

    return letters_count;
}


int count_spaces(string text)
{
    int spaces_count = 0;

    for(int index = 0, text_len = strlen(text); index < text_len; index++)
    {
        if (text[index] == ' ')
        {
            spaces_count++;
        }
    }

    return spaces_count;
}


int count_sentences(string text)
{
    int sentences_count = 0;

    for(int index = 0, text_len = strlen(text); index < text_len; index++)
    {
        if(text[index] == '.' || text[index] == '!' || text[index] == '?')
        {
            sentences_count++;
        }
    }

    return sentences_count;
}