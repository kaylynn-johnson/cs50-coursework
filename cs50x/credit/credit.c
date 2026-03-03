#include <cs50.h>
#include <stdio.h>
#include <string.h>

string determine_card_type(string str_num, int num_len);
string determine_valid_checksum(string str_num, int num_len);

int main(void)
{
    // Get input from user
    long credit_num = get_long("What is your credit card number? ");

    // Create input variables
    char str_num[20];
    sprintf(str_num, "%ld", credit_num);
    int num_len = strlen(str_num);

    // Check output from user
    string card_type = determine_card_type(str_num, num_len);

    // Report INVALID if card_type returns incorrect length/initial digits
    if (strcmp(card_type, "INVALID") == 0)
    {
        printf("%s\n", card_type);
        return 0;
    }

    // Calculate checksum
    string valid_checksum = determine_valid_checksum(str_num, num_len);

    if (strcmp(valid_checksum, "VALID") == 0)
    {
        printf("%s\n", card_type);
        return 0;
    }
    else
    {
        printf("%s\n", valid_checksum);
        return 0;
    }
}

string determine_card_type(string str_num, int num_len)
{
    if ((num_len == 13) && (str_num[0] == '4'))
    {
        // Is a possible VISA card number
        return "VISA";
    }
    else if (num_len == 15 && (str_num[0] == '3' && (str_num[1] == '4' || str_num[1] == '7')))
    {
        // Is a possible AMEX card number
        return "AMEX";
    }
    else if ((num_len == 16) && (str_num[0] == '5' && (str_num[1] > '0' && str_num[1] < '6')))
    {
        // Is a possible MASTERCARD card number
        return "MASTERCARD";
    }
    else if ((num_len == 16) && (str_num[0] == '4'))
    {
        // Is a possible VISA card number
        return "VISA";
    }
    else
    {
        // Is an invalid card number
        return "INVALID";
    }
}

string determine_valid_checksum(string str_num, int num_len)
{
    // Initialize part one variables
    int part1_sum = 0;
    int inter_digit;
    char str_double[3];

    // Loop through every other digit starting with second to last
    for (int i = num_len - 2; i > -1; i -= 2)
    {
        // Calculate the double of every other digit starting with second to last
        inter_digit = (str_num[i] - '0') * 2;
        // Assign to a string since these digits need to be added together
        sprintf(str_double, "%i", inter_digit);
        // Keep a running sum of these digits
        for (int j = 0; j < strlen(str_double); j++)
        {
            part1_sum += (str_double[j] - '0');
        }
    }

    // Initialize part two variables
    int part2_sum = part1_sum;

    // Loop through every other digit starting with last
    for (int k = num_len - 1; k > -1; k -= 2)
    {
        inter_digit = str_num[k] - '0';
        part2_sum += inter_digit;
    }

    // Determine if modulo 10 equals 0
    if ((part2_sum % 10) == 0)
    {
        return "VALID";
    }
    else
    {
        return "INVALID";
    }
}
