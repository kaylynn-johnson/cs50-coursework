#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Gather all the input from the user
    string name = get_string("What is your name? ");
    int age = get_int("How old are you? ");
    string phone_num = get_string("What is your phone number with dashes? ");
    string city = get_string("What city do you live in? ");
    string state = get_string("What state do you live in? ");

    // Now add everything together
    printf("New contact: %s, %i, lives in %s, %s and can be reached at %s.\n", name, age, city, state, phone_num);
}
