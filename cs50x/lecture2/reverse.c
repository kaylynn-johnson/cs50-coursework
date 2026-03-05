#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string phrase = get_string("Text: ");

    printf("Reverse: ");
    
    for (int i = strlen(phrase); i > -1; i--)
    {
        printf("%c", phrase[i]);
    }
    printf("\n");
}
