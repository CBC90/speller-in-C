// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Word Count
int COUNT = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char wordbuffer[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", wordbuffer) != EOF)
    {

        COUNT++;

        //Create temporary new node
        node *new_node = malloc(sizeof(node));

        // make sure new node memory allocation succeeded
        if (new_node == NULL)
        {
            // value is null
            printf("New cursor memory allocation returned NULL\n");
            return false;
        }

        //Fill in the new node's fields
        new_node->next = NULL;
        strcpy(new_node->word, wordbuffer);

        int i = hash(new_node->word);

        // Places new node at the beginning of its corresponding hashtable bucket
        new_node->next = hashtable[i];
        hashtable[i] = new_node;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;

    // Run dictionary once in order to determine length of each linked list and position of second letter
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return COUNT;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Convert word to lower case
    int length = strlen(word);
    char wordl[length + 1];
    for (int i = 0; i < length; i++)
    {
        wordl[i] = tolower(word[i]);
    }
    wordl[length] = '\0';

    // Creates cursor in the currect bucket and iterates until the two words match
    int letter1 = hash(word);
    //int letter2 = hash1(word);
    node *cursor = hashtable[letter1];

    //int search_count = 0;
    while (cursor != NULL)
    {

        if (strcasecmp(cursor->word, wordl) != 0)
        {

            cursor = cursor->next;
        }
        else
        {
            return true;
        }
        //search_count++;
    }
    return false;
}

bool unload(void)
{
    for (int j = 0; j < N; j++)
    {
        node *cursor = hashtable[j];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
