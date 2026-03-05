#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc < 3)
    {
        // User input is not correct
        printf("Usage: ./initials First Last\n");
        return 1;
    }
    // User input the correct arguments (either middle name or not)
    for (int i = 1; i < argc; i++)
    {
        printf("%c", argv[i][0]);
    }
    printf("\n");
}
