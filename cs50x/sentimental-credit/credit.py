import cs50
import sys

# Get input from user
credit_num = cs50.get_string("Number: ")

# Check output from user
credit_num_len = len(credit_num)
if ((credit_num_len == 13 or credit_num_len == 16) and credit_num[0] == '4'):
    credit_type = 'VISA'
elif (credit_num_len == 15 and (credit_num[:2] == '34' or credit_num[:2] == '37')):
    credit_type = 'AMEX'
elif (credit_num_len == 16 and (int(credit_num[:2]) > 50 and int(credit_num[:2]) < 56)):
    credit_type = 'MASTERCARD'
else:
    # Report INVALID if needed
    sys.exit("INVALID")

# Calculate checksum
sum = 0
for num in range(credit_num_len - 2, -1, -2):
    # multiple the digit by 2; if double digit, add the two digits
    mult = int(credit_num[num]) * 2
    for digit in str(mult):
        sum += int(digit)

for num in range(credit_num_len - 1, -1, -2):
    # add each digit to the sum
    sum += int(credit_num[num])

# Report INVALID or Card type
if sum % 10 == 0:
    print(credit_type)
else:
    print("INVALID")
