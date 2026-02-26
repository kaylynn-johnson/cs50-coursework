#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = -1;

    while (n < 0)
    {
        n = get_int("What's n? ");
    }

    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
