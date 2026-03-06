#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

int check_key(string key);

int main(int argc, string argv[])
{
    // check for valid number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check for valid key
    int good = check_key(argv[1]);
    if (!good)
    {
        return 1;
    }

    // ask for plaintext input from user

    // encrypt the text
    // declare string of same length as plaintext to add to in loop
    // find number of letter in plaintext in alphabet (subtract 65 or 97)
    // replace with new letter from key
    // ensure to preserve case and don't change punctuation

    // print out "ciphertext: " and then the string from above
}

int check_key(string key)
{
    // length must be ALPHABET_SIZE
    if (strlen(key) != ALPHABET_SIZE)
    {
        printf("Key must contain %i characters.\n", ALPHABET_SIZE);
        return 1;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (isalpha(key[i]) == 0) // key should be alphabetical
        {
            printf("Key must be alphabetical.\n");
            return 1;
        }

        for (int j = 0; j < ALPHABET_SIZE; j++)
        {
            if (key[i] == key[j] && i != j)
            {
                // found a duplicate letter
                printf("Key must contain only one instance of each character.\n");
                return 1;
            }
        }
    }

    // output is good
    return 0;
}
