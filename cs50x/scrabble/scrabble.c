#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Declarations
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int scores[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
#define ALPHABET_SIZE 26
int determine_word_score(string word);
int determine_letter_score(char letter);

int main(void)
{
    // Get input from two players
    string player1_word = get_string("Player 1: ");
    string player2_word = get_string("Player 2: ");

    // Determine word score
    int player1_score = determine_word_score(player1_word);
    int player2_score = determine_word_score(player2_word);

    // Compare player1's score vs player2's score
    if (player1_score > player2_score)
    {
        printf("Player 1 Wins!\n");
    }
    else if (player2_score > player1_score)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int determine_word_score(string word)
{
    int word_score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Find scrablle score for letter and add to running sum
        word_score += determine_letter_score(tolower(word[i]));
    }

    return word_score;
}

int determine_letter_score(char letter)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (letter == letters[i])
        {
            // return score at same i location
            return scores[i];
        }
    }
    return 0;
}
