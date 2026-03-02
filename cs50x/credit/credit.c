#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //get input from user
    long credit_num = get_long("What is your credit card number? ");

    // check output from user
    // call the function
}


str check_output(num)
{
    int num_len = strlen(num);

    if (num_len == 13 || num_len == 14) && (num[0] == 4) {
        // Is a possible VISA card number
        return "VISA";
    }
    elif (num_len == 15 && (num[0:1] == 34 || num[0:1] == 37)) {
        // Is a possible AMEX card number
        return "AMEX";
    }
    elif (num_len == 15 && (num[0] == 4)) {
        // Is a possible VISA card number
        return "VISA";
    }
    elif ((num_len == 16) && (num[0:1] > 50 & num[0:1] < 56)) {
        // Is a possible MASTERCARD card number
        return "MASTERCARD";
    }
    elif ((num_len == 16) && (num[0] == 4)) {
        // Is a possible VISA card number
        return "VISA";
    }
    else {
        // Is an invalid card number
        return "INVALID";
    }
}
