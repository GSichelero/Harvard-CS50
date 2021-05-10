// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 677;

// Hash table
node *table[N];

// Number of words in the dictionary
int number_of_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_table_index = hash(word);
    node *cursor = table[hash_table_index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char first_letter = word[0];
    char second_letter = word[1];
    int first_int;
    int second_int;

    if (first_letter >= 'a' && first_letter <= 'z')
    {
        first_int = first_letter - 'a';
    }
    else if (first_letter >= 'A' && first_letter <= 'Z')
    {
        first_int = first_letter - 'A';
    }
    else
    {
        return 676;
    }

    if (second_letter >= 'a' && second_letter <= 'z')
    {
        second_int = second_letter - 'a';
    }
    else if (second_letter >= 'A' && second_letter <= 'Z')
    {
        second_int = second_letter - 'A';
    }
    else
    {
        return first_int;
    }

    return ((first_int + 1) * 26) + second_int;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    char word[LENGTH + 1];

    for (int i = 0; i < N; i++)
        {
            table[i] = NULL;
        }

    // dict = fopen(dictionary, "r");

    if (dict != NULL)
    {
        while(fscanf(dict, "%s", word) != EOF)
        {
            node *n = malloc(sizeof(node));
            if (n != NULL)
            {
                number_of_words++;

                strcpy(n->word, word);
                n->next = NULL;

                int word_hash_table_index = hash(word);

                if (table[word_hash_table_index] == NULL)
                {
                    table[word_hash_table_index] = n;
                    n->next = NULL;
                }
                else
                {
                    n->next = table[word_hash_table_index];
                    table[word_hash_table_index] = n;
                }
            }
            else
            {
                number_of_words = 0;
                fclose(dict);
                return false;
            }
        }
    }
    else
    {
        number_of_words = 0;
        fclose(dict);
        return false;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return number_of_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int hash_table_index = 0; hash_table_index < N; hash_table_index++)
    {
        node *cursor = table[hash_table_index];
        node *tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
