def main():
    text = input("Text: ")

    letters = sum(c.isalpha() for c in text)
    words  = text.count(" ") + 1
    sentences = text.count("?") + text.count(".") + text.count("!")

    letters_per_100_word = letters / (words / 100)
    sentences_per_100_word = sentences / (words / 100)
    index = (0.0588 * letters_per_100_word) - (0.296 * sentences_per_100_word) - 15.8

    if index <= 0.5:
        print("Before Grade 1")
    elif index >= 15.5:
        print("Grade 16+")
    else:
        print(f"Grade {int(round(index, 0))}")

if __name__ == "__main__":
    main()