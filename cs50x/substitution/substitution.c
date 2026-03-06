#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define UPPER 65
#define LOWER 97

int check_key(string key);
string encrypt_text(string key, string plaintext, char ciphertext);

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
    string plaintext = get_string("plaintext: ");

    // encrypt the text
    char ciphertext[strlen(plaintext)];
    string complete_ciphertext = encrypt_text(argv[1], plaintext, ciphertext);

    // print out "ciphertext: " and then the string from above
    printf("ciphertext: %s\n", complete_ciphertext);
    return 0;
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

string encrypt_text(string key, string plaintext, char ciphertext)
{
    // declare string of same length as plaintext


    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // check if uppercase letter
        if (isalpha(plaintext[i]) && isupper(plaintext[i]))
        {
            // find location in the alphabet
            int letter_location = plaintext[i] - UPPER;
            ciphertext[i] = toupper(key[letter_location]);
        }
        else if (isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            // find location in the alphabet
            ciphertext[i] = tolower(key[plaintext[i] - LOWER]);
        }
        else
        {
            // not a letter so keep the same
            ciphertext[i] = plaintext[i];
        }
    }

    return ciphertext;
}
