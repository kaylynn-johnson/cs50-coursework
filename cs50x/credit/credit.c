#include <cs50.h>
#include <stdio.h>
#include <string.h>

string check_output(num_input);
string calculate_checksum(num_input);

int main(void)
{
    //get input from user
    long credit_num = get_long("What is your credit card number? ");

    // check output from user
    // call the function
    string card_type = check_output(credit_num);

    // just report invalid if that is the return on check output
    if (card_type == "INVALID") {
        printf("%s\n", card_type);
        return;
    }

    // calculate checksum
    // call the function
    string valid_checksum = calculate_checksum(credit_num);

    if (valid_checksum == "VALID") {
        printf("%s\n", card_type);
        return;
    }
    else {
        printf("%s\n", valid_checksum);
        return;
    }
}


string check_output(num_input)
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


string calculate_checksum(num)
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
