import math


def main():
    text = str(input("Text: "))
    grade = grade_text(text)
    if grade >= 1 and grade <= 16:
        print(f"Grade {grade}")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print("Grade 16+")


def grade_text(t):
    sentence_count, letter_count, word_count = 0, 0, 0
    for letter in t:
        if letter.isalpha():
            letter_count += 1
        elif letter in ['!', '?', '.']:
            sentence_count += 1
        elif letter == " ":
            word_count += 1
    if word_count > 0:
        word_count += 1
    index = (0.0588 * (letter_count / word_count) * 100.0) \
        - (0.296 * (sentence_count / word_count) * 100.0) - 15.8
    return round(index)


if __name__ == "__main__":
    main()
