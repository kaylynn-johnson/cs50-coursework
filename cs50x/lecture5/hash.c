#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    char *input = get_string("Word: ");

    int hash_num = toupper(input[0]) - 'A';

    printf("The hash number is %i\n", hash_num);
}
