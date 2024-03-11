// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];
int word_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *n = table[index];
    for (node *current = n; current != NULL; current = current->next)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (word == NULL || word[0] == '\0')
    {
        return 0;
    }

    char first = toupper(word[0]);
    char second = toupper(word[1]);

    if (!isalpha(first) || !isalpha(second))
    {
        return 0;
    }

    return ((first - 'A') * 26) + (second - 'A');
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dic_file = fopen(dictionary, "r");
    if (dic_file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(dic_file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        strcpy(n->word, word);
        n->next = NULL;
        int index = hash(n->word);
        word_counter++;

        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }
    fclose(dic_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current = NULL;
    node *n = NULL;
    for (int i = 0; i < N; ++i)
    {
        n = table[i];
        while (n != NULL)
        {
            current = n;
            n = n->next;
            free(current);
        }
        table[i] = NULL;
    }
    return true;
}
