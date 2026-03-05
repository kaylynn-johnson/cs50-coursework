#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string phrase = get_string("Input: ");

    int i = 0;
    while (phrase[i] != '\0' && phrase[i+1] != '\0')
    {
        if (phrase[i] > phrase[i+1])
        {
            printf("No\n");
            return 0;
        }
        i++;
    }
    printf("Yes\n");
}
