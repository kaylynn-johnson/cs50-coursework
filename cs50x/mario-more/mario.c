#include <cs50.h>
#include <stdio.h>

void print_dynamic_spaces(int row, int height);
void print_dynamic_hashtags(int row);

int main(void)
{
    // Ask user for input
    int height;
    do
    {
        height = get_int("What height do you want the pyramid to be (between 1-8 inclusive)? ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        // call dynamic spacing function with height and i as inputs
        print_dynamic_spaces(i, height);

        // call dynamic hashtag function with i as input
        print_dynamic_hashtags(i);

        // write two spaces
        printf("  ");

        // call dynamic hashtag function with i as input
        print_dynamic_hashtags(i);

        // write new line
        printf("\n");
    }
}

void print_dynamic_spaces(int row, int height)
{
    for (int i = height - row; i > 0; i--)
    {
        printf(" ");
    }
}

void print_dynamic_hashtags(int row)
{
    for (int i = 0; i < row; i++)
    {
        printf("#");
    }
}
