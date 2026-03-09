#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    // Get info from user
    int num = get_int("Number: ");

    // Call collatz function with input
    int num_steps = collatz(num);

    // Print out number of steps
    printf("It took %i step(s) to reach 1.\n", num_steps);
}

int collatz(int n)
{
    // Base case
    if (n == 1)
        return 0;

    // Recursive cases
    if (n % 2 == 0)
    {
        // even
        return 1 + collatz(n / 2);
    }
    else
    {
        // odd
        return 1 + collatz(3 * n + 1);
    }
}
