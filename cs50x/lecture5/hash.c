#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char *input = get_string("Word: ");

    int hash_num = input[0].toupper() - 'A';

    printf("The hash number is %i\n", hash_num);
}
