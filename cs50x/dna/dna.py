import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Incorrect number of arguments")
        sys.exit()

    # Read database file into a variable
    with open(sys.argv[1], 'r') as db_file:
        header = db_file.readline()
        db_lines = db_file.readlines()

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as dna_file:
        dna_seq = dna_file.readline().strip('\n')

    # Find longest match of each STR in DNA sequence
    # loop over header columns to get the STR options
    STR_options = header.strip('\n').split(',')[1:]
    STR_list = []
    for str_seq in STR_options:
        STR_list.append(str(longest_match(dna_seq, str_seq)))

    # Check database for matching profiles
    for db_entry in db_lines:
        entry = db_entry.strip('\n').split(',')[1:]
        if entry == STR_list:
            # Matches the DNA profile
            print(db_entry.split(',')[0])
            break
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
