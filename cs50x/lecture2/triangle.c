#include <cs50.h>
#include <stdio.h>

bool valid_triangle(int a, int b, int c);

int main(void)
{
    int side1 = get_int("Side 1: ");
    int side2 = get_int("Side 2: ");
    int side3 = get_int("Side 3: ");

    bool valid = valid_triangle(side1, side2, side3);

    if (valid)
    {
        printf("The triangle is valid.\n");
    }
    else
    {
        printf("The triangle is not valid.\n");
    }


}

bool valid_triangle(int a, int b, int c)
{
    if (a < 1 || b < 1 || c < 1)
    {
        return false;
    }

    if ((a + b) < c)
    {
        return false;
    }
    else if ((b + c) < a)
    {
        return false;
    }
    else if ((a + c) < b)
    {
        return false;
    }
    else
    {
        return true;
    }
}
