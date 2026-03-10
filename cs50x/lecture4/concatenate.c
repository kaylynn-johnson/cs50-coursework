#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *concat(char *s1, char*s2);

int main(void)
{
    char *s1 = get_string("String 1: ");
    char *s2 = get_string("String 2: ");

    char *s3 = concat(s1, s2);

    printf("%s\n", s3);
    free(s3);
}

char *concat(char *s1, char *s2)
{
    // Get memory for s3 (strlen(s1) + strlen(s2))
    char *s3 = malloc(strlen(s1) + strlen(s2) + 1);

    // Copy over the values from s1 and s2
    for (int i = 0, n = strlen(s1); i < n; i++)
    {
        s3[i] = s1[i];
    }
    for (int j = 0, n = strlen(s2); j < n + 1; j++)
    {
        s3[j + strlen(s1)] = s2[j];
    }
    s3[strlen(s1) + strlen(s2)] = '\0';

    // Return s3
    return s3;
}
