# TODO
import re


def main():
    print("Text: ", end="")
    text = input()

    # Letters: any lower case or upper case character
    letters = len(re.findall("[a-zA-Z]", text))

    # Words: Looks for one or more character groups that don't include white spaces or line breaks
    words = len(re.findall("[^ \n]+", text))

    # Sentences: any groups of punctuation characters (!.?) (!!! counts as one sentece)
    sentences = len(re.findall("[!.?]+", text))

    L = (letters * 100.0) / words                   # Letters per 100 words
    S = (sentences * 100.0) / words                 # Sentences per 100 words

    grade = ColemanLiau(L, S)                       # Calculate the Coleman-Liau index

    # Printing the grade level
    if grade >= 16:
        print("Grade 16+")

    elif grade < 1:
        print("Before Grade 1")

    else:
        print(f"Grade {grade}")

# Coleman-Liau index formula


def ColemanLiau(L, S):
    return round(0.0588 * L - 0.296 * S - 15.8)


main()