#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

int main(int argc, string argv[])
{
    // check for valid number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check for valid key
    // length must be 26 (magic number)
    if (strlen(argv[1]) != ALPHABET_SIZE)
    {
        printf("Key must contain %i characters.\n", ALPHABET_SIZE);
        return 1;
    }
    // key should be alphabetical
    for (int k = 0; k < ALPHABET_SIZE; k++)
    {
        if (isalpha(argv[1][k]) == 0)
        {
            printf("Key must be alphabetical.\n");
            return 1;
        }
    }

    // each letter should only be used once (nested for loop)
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        for (int j = 0; j < ALPHABET_SIZE; j++)
        {
            if (argv[i] == argv[j] && i != j)
            {
                // found a duplicate
                printf("Key must contain only one instance of each character.\n");
                return 1;
            }
        }
    }

    // ask for plaintext input from user

    // encrypt the text
    // declare string of same length as plaintext to add to in loop
    // find number of letter in plaintext in alphabet (subtract 65 or 97)
    // replace with new letter from key
    // ensure to preserve case and don't change punctuation

    // print out "ciphertext: " and then the string from above
}
