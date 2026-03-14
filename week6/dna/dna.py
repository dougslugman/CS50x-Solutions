import csv
import sys


def main():
    table = []
    strnums = []
    if len(sys.argv) != 3:
        print("Usage: ./dna file.csv file.txt")
        return
    else:
        FILEpeople = sys.argv[1]
        FILEstrand = sys.argv[2]

    with open(FILEstrand, "r") as file:
        strand = file.readline().strip()

    with open(FILEpeople, "r") as file:
        for line in file:
            line = line.strip().split(',')
            table.append(line)

    for i in range(1, len(table[0])):
        ustr = longest_match(strand, table[0][i])
        strnums.append(ustr)

    for i in range(1, len(table)):
        if strnums == [int(table[i][x]) for x in range(len(table[i])) if x != 0]:
            print(table[i][0])
            return
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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
