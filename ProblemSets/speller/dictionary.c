// Implements a dictionary's functionality

#include "dictionary.h"
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int totalWords = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Hash table
const unsigned int N = 26;
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // printf("First word under first hash %s", table[0]->word);
    //  get first letter lowercase and figure out hash
    int hashref = hash(word);

    // follow chain in hash table and string compare until match is found
    node hashNode = *table[hashref];

    // start looping through
    while (hashNode.next != NULL)
    {
        if (strcasecmp(hashNode.word, word) == 0)
        {
            return true;
        }
        hashNode = *hashNode.next;
    }
    // check first element
    if (strcasecmp(hashNode.word, word) == 0)
    {
        return true;
    }
    // if no match
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // determine where in hash table by getting first letter
    int hashRef = (tolower(word[0]) - 97);

    // check we're between a and z
    if (hashRef < 0 || hashRef > 25)
    {
        return false;
    }

    return hashRef;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        return 1;
    }

    // store each char in tmp, check if alpha, then add to word
    char *tmp = malloc(sizeof(char));
    char *newdictWord = malloc(sizeof(char) * LENGTH);
    int j = 0;

    while (fread(tmp, sizeof(char), 1, source) != 0)
    {
        if ((isalpha(*tmp) != 0 || *tmp == '\'') && (j < LENGTH))
        {
            newdictWord[j] = *tmp;
            j++;
        }
        else if (j > LENGTH)
        {
            printf("Word longer than allowed encountered in dictionary.");
            return false;
        }
        // encounter non-alphanumeric (space, new line, etc.)
        else if (isalpha(*tmp) == 0)
        {
            int hashref = hash(newdictWord);

            // allocate memory for new node
            node *n = malloc(sizeof(node));

            // if hash table is populated at that element ()
            if (table[hashref] != NULL)
            {
                n->next = table[hashref];
            }
            else
            {
                n->next = NULL;
            }

            // update has table with current node's pointer

            strcpy(n->word, newdictWord);
            // n->next = NULL;
            table[hashref] = n;
            j = 0;
            memset(tmp, 0, LENGTH);
            memset(newdictWord, 0, LENGTH);
            size();
        }
    }
    // printf("%s \n", table[25]->word);
    // printf("%s \n", table[25]->next->word);
    // printf("%i", totalWords);

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size()
{
    totalWords++;
    if (totalWords != 0)
    {
        return (totalWords - 1);
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            node *next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }

    return true;
}
