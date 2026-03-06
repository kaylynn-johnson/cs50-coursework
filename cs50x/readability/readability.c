#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_num_words(string text);
int calculate_num_letters(string text);
int calculate_num_sentences(string text);

int main(void)
{
    // Ask for text
    string text = get_string("Text: ");

    // Calculate number of words in the text (1)
    int num_words = calculate_num_words(text);
    printf("Number of words: %i\n", num_words);

    // Calculate number of letters in the text (2)
    int num_letters = calculate_num_letters(text);
    printf("Number of letters: %i\n", num_letters);

    // Calculate number of sentences in the text (3)
    int num_sentences = calculate_num_sentences(text);
    printf("Number of sentences: %i\n", num_sentences);

    // Calculate L = (2) / (1) * 100
    float L = (num_letters / num_words) * 100.0;

    // Calculate S = (3) / (1) * 100
    float S = (num_sentences / num_words) * 100.0;

    // Run the equation (0.0588 * L) - (0.296 * S) - 15.8
    int grade_level = (0.0588 * L) - (0.296 * S) - 15.8;

    // Print out the appropriate grade level
    if (grade_level < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }

}

int calculate_num_words(string text)
{
    // increment counter when see a " " (space) or ASCII 32
    int num_words = 1;  // starting at 1 to capture last word that won't have a space
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32) {
            num_words++;
        }
    }

    return num_words;
}

int calculate_num_letters(string text)
{
    // increment counter when see a letter (between 97-122) after lowering text
    int num_letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (tolower(text[i]) >= 97 && tolower(text[i]) <= 122)
        {
            // This is a letter
            num_letters++;
        }
    }

    return num_letters;
}

int calculate_num_sentences(string text)
{
    // increment counter when see a ".", "!", or "?" or ASCII 33, 46, 63
    int num_sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            // There is an end of sentence punctuation
            num_sentences++;
        }
    }

    return num_sentences;
}
