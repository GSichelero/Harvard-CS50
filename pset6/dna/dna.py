import csv
import sys

def verify_sequence_len(character_index, STR, value, STR_char_count, DNA_sequence):
    sequence_tmp = 0
    while DNA_sequence[character_index : character_index + STR_char_count] == STR:
        sequence_tmp = sequence_tmp + 1
        character_index = character_index + STR_char_count
    if value < sequence_tmp:
        value = sequence_tmp
    return value

def main():
    if len(sys.argv) != 3:
        print("Incorrect Number of Arguments")
        return 1
    individuals_STR_counts = csv.DictReader(open(sys.argv[1], 'r'))
    DNA_sequence = str(open(sys.argv[2]).read())

    all_STRS = individuals_STR_counts.fieldnames[1:]
    maximun_number_of_STR_sequences = {}
    for STR in all_STRS:
        STR_char_count = len(STR)
        maximun_number_of_STR_sequences[STR] = 0
        for character_index in range(0, len(DNA_sequence) - (STR_char_count - 1)):
            maximun_number_of_STR_sequences[STR] = verify_sequence_len(character_index, STR, maximun_number_of_STR_sequences[STR], STR_char_count, DNA_sequence)

    for row in individuals_STR_counts:
        if all(maximun_number_of_STR_sequences[STR] == int(row[STR]) for STR in all_STRS):
            print(row["name"])
            return 0

    print("No match")
    return 0

if __name__ == "__main__":
    main()