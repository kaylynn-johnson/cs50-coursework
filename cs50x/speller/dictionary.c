// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get hash for the word to know which table index to look at
    int index = hash(word);
    node *trav = table[index];
    while (trav != NULL)
    {
        for (int i = 0; word[i] != '\0'; i++)
        {
            //compare character by character
            
        }
        if (strcmp(trav->word, tolower(word)) == 0)
        {
            return true;
        }
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        //couldn't open the dictionary
        return false;
    }

    // read each line (look for the \n char)
    char *letter = malloc(sizeof(char));
    if (letter == NULL)
    {
        return false;
    }
    // char *running_word[LENGTH+1];
    int counter = 0;
    node *found_word;
    while(fread(letter, 1, 1, dict) != 0)
    {
        // reading letter by letter
        if (counter == 0)
        {
            //create a new node
            found_word = malloc(sizeof(node));
            if (found_word == NULL)
            {
                return false;
            }
            // found_word->word[counter] = *letter;
            // counter++;
        }

        if (*letter == '\n')
        {
            // reached the end of a word
            // don't need to add the new line character to the found_word
            // now add the final word to the hash
            int index = hash(found_word->word);
            found_word->next = table[index];
            table[index] = found_word;
            counter = 0;
        }
        else
        {
            found_word->word[counter] = *letter;
            counter++;
        }

    }
    free(letter);
    // add each line to the hash table (starting with alphabet + linked list)
    // close dictionary file
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // nested for loops to loop through index of table and then linked list along there
    // think of creating a global variable that is incremented when loading
    unsigned int counter = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *trav = table[i]; trav != NULL; trav = trav->next)
        {
            counter++;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // nested for loop again for each part of hash table
    for (int i = 0; i < N; i++)
    {
        node *trav = table[i];
        while (trav != NULL)
        {
            node *tmp = trav;
            trav = trav->next;
            free(tmp);
        }
    }
    return true;
}
