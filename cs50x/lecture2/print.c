#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string word = get_string("Input: ");

    int i = 0;
    while (word[i] != '\0')
    {
        printf("%c", word[i]);
        i++;
    }

    printf("\n");
}
