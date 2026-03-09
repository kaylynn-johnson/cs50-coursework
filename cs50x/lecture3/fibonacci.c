#include <cs50.h>
#include <stdio.h>

int fib(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("What is N? ");
    } while (n < 1);

    printf("The %ith Fibonacci number is %i.\n", n, fib(n));
}

int fib(int n)
{
    // Base Case
    if (n == 1)
    {
        return 0;
    }
    if (n == 2)
    {
        return 1;
    }

    // Recursion case
    return fib(n-1) + fib(n-2);
}
