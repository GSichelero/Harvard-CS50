#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int verify_repeated_letters(string text);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Command not found!\n");
        return 1;
    }
    else
    {
        int length = strlen(argv[1]);
        if (length != 26)
        {
            printf("The key must have 26 characteres!\n");
            return 1;
        }
        else
        {
            for (int i = 0; i < length; i++)
            {
                if (argv[1][i] < 'A' || argv[1][i] > 'z')
                {
                    printf("The key must not contain special characteres!\n");
                    return 1;
                }
                else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
                {
                    argv[1][i] = argv[1][i] - 32;
                }
            }

            if (verify_repeated_letters(argv[1]) == 1)
            {
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        char letter_plain = plaintext[i];

        for (int j = 0; j < 26; j++)
        {
            char letter_cipher = argv[1][j];
            char letter_cipher_lower = letter_cipher + 32;
            char letter_alphabet = alphabet[j];
            char letter_alphabet_upper = letter_alphabet + 32;

            if (letter_plain == letter_alphabet)
            {
                ciphertext[i] = letter_cipher;
            }
            else if (letter_plain == letter_alphabet_upper)
            {
                ciphertext[i] = letter_cipher_lower;
            }
        }
    }
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}


int verify_repeated_letters(string text)
{
    for (int i = 0; i < 26; i++)
    {
        char letter_one = text[i];

        for (int j = i + 1; j < 26; j++)
        {
            char letter_two = text[j];

            if (letter_one == letter_two)
            {
                printf("The key must not contain 2 or more equal letters!\n");
                return 1;
            }
        }
    }
    return 0;
}