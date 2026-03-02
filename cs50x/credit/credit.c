#include <cs50.h>
#include <stdio.h>
#include <string.h>

string check_output(long num);
string calculate_checksum(long num);

int main(void)
{
    // get input from user
    long credit_num = get_long("What is your credit card number? ");

    // check output from user
    // call the function
    string card_type = check_output(credit_num);
    // printf("%s\n", card_type);

    // just report invalid if that is the return on check output
    if (strcmp(card_type, "INVALID") == 0)
    {
        printf("%s\n", card_type);
        return 0;
    }

    // calculate checksum
    // call the function
    string valid_checksum = calculate_checksum(credit_num);
    // printf("%s\n", valid_checksum);

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

string check_output(long num)
{
    char str_num[20];
    sprintf(str_num, "%ld", num);
    // printf("%s\n", str_num);
    int num_len = strlen(str_num);
    // printf("%i\n", num_len);
    // printf("%c\n", str_num[0]);

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

string calculate_checksum(long num)
{
    char str_num[20];
    sprintf(str_num, "%ld", num);
    printf("%s\n", str_num);
    int num_len = strlen(str_num);

    int part1_sum = 0;
    int inter_digit;
    printf("%i\n", (str_num[0]));
    for (int i = num_len - 2; i > -1; i -= 2)
    {
        part1_sum += (str_num[i] * 2);
    }
    printf("%i\n", part1_sum);

    int part2_sum = 0;
    char str_part1[5];
    sprintf(str_part1, "%i", part1_sum);
    int part1_len = strlen(str_part1);
    for (int j = 0; j < part1_len; j++)
    {
        part2_sum += str_part1[j];
    }
    printf("%i\n", part2_sum);

    int part3_sum = part2_sum;
    for (int k = 0; k < num_len; k += 2)
    {
        part3_sum += str_num[k];
    }
    printf("%i\n", part3_sum);

    if (part3_sum % 10)
    {
        return "VALID";
    }
    else
    {
        return "INVALID";
    }
}
