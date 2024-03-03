#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float grade_texts(string s);

int main(void)
{
    string text = get_string("Text: ");
    int grade = round(grade_texts(text));
    if (grade >= 1 && grade <= 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// Grade function
float grade_texts(string t)
{
    float sentence_count = 0.0;
    float letter_count = 0.0;
    int word_count = 0;

    for (int i = 0, length = strlen(t); i < length; ++i)
    {
        if ((t[i] >= 65 && t[i] <= 90) || (t[i] >= 97 && t[i] <= 122))
        {
            letter_count++;
        }
        else if (t[i] == '.' || t[i] == '!' || t[i] == '?')
        {
            sentence_count++;
        }
        else if (t[i] == ' ')
        {
            word_count++;
        }
    }
    if (letter_count > 0)
    {
        word_count++;
    }
    float index = (0.0588 * ((letter_count / word_count) * 100.0)) - (0.296 * ((sentence_count / word_count) * 100.0)) - 15.8;
    return index;
}
