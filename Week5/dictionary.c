// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const uint16_t N = 65535;
const int node_size = sizeof(node);
// Hash table
node *table[N];
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_value = hash(word);

    if (table[hash_value] == NULL)
    {
        return false;
    }
    else
    {
        node *cursor = table[hash_value];
        while (cursor != NULL)
        {
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    uint16_t hash_value = 0;
    for (uint8_t i = 0, n = strlen(word); i < n; i++)
    {
        hash_value += (uint8_t) tolower(word[i]) * (i + 1);
        hash_value *= hash_value;
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[LENGTH + 1];
    FILE *dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        return false;
    }

    while (fscanf(dict_ptr, "%s", word) != EOF)
    {
        unsigned int hash_value = hash(word);
        node *new_node = calloc(1, node_size);

        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, word);
        new_node->next = NULL;

        if (table[hash_value] == NULL)
        {
            table[hash_value] = new_node;
        }
        else
        {
            new_node->next = table[hash_value];
            table[hash_value] = new_node;
        }
        word_count++;
    }

    fclose(dict_ptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *temp = cursor;

        while (cursor != NULL)
        {

            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }

    return true;
}