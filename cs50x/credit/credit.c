#include <cs50.h>
#include <stdio.h>
#include <string.h>

string check_output(long num);
string calculate_checksum(long num);

int main(void)
{
    //get input from user
    long credit_num = get_long("What is your credit card number? ");

    // check output from user
    // call the function
    string card_type = check_output(credit_num);

    // just report invalid if that is the return on check output
    if (strcmp(card_type, "INVALID") == 0) {
        printf("%s\n", card_type);
        return 0;
    }

    // calculate checksum
    // call the function
    string valid_checksum = calculate_checksum(credit_num);

    if (strcmp(valid_checksum, "VALID") == 0) {
        printf("%s\n", card_type);
        return 0;
    }
    else {
        printf("%s\n", valid_checksum);
        return 0;
    }
}


string check_output(long num)
{
    char str_num[20];
    sprintf(str_num, "%ld", num);
    //printf(str_num);
    int num_len = strlen(str_num);

    if ((num_len == 13 || num_len == 14) && (str_num[0] == 4)) {
        // Is a possible VISA card number
        return "VISA";
    }
    else if (num_len == 15 && (str_num[0:1] == 34 || str_num[0:1] == 37)) {
        // Is a possible AMEX card number
        return "AMEX";
    }
    else if (num_len == 15 && (str_num[0] == 4)) {
        // Is a possible VISA card number
        return "VISA";
    }
    else if ((num_len == 16) && (str_num[0:1] > 50 & str_num[0:1] < 56)) {
        // Is a possible MASTERCARD card number
        return "MASTERCARD";
    }
    else if ((num_len == 16) && (str_num[0] == 4)) {
        // Is a possible VISA card number
        return "VISA";
    }
    else {
        // Is an invalid card number
        return "INVALID";
    }
}


string calculate_checksum(long num)
{
    int num_len = strlen(num);

    int part1_sum = 0;
    for (int i = num_len - 2; i > -1; i -= 2) {
        part1_sum += (num[i] * 2);
    }

    int part2_sum = 0;
    for (int j = 0; j < strlen(string part1sum = part1_sum); j++) {
        part2_sum += part1sum[j];
    }

    int part3_sum = part2_sum;
    for (int k = 0; k < num_len; k += 2) {
        part3_sum += num[k];
    }

    if (part3_sum % 10) {
        return "VALID";
    }
    else {
        return "INVALID";
    }
}
