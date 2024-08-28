from cs50 import get_string
import re


def main():
    input = get_string("Text: ")

    letters = sum(map(str.isalpha, input))
    words = len(str.split(input))
    sentences = (len(re.findall(r'(\.|\?|\!)', input)))

    index = round(0.0588 * (letters/words*100) - 0.296 * (sentences/words*100) - 15.8)

    if index < 1.0:
        print("Before Grade 1")
    elif (index >= 1 and index <= 16.0):
        print(f"Grade {index}")
    elif index > 16.0:
        print("Grade 16+")


main()
