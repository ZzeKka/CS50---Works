#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int count_points(string word);

int main(void)
{
    // input
    string p1_word = get_string("Player1: ");
    string p2_word = get_string("Player2: ");

    // calculate points
    int p1_points = count_points(p1_word);
    int p2_points = count_points(p2_word);

    if (p1_points == p2_points)
    {
        printf("Tie!\n");
    }
    else
    {
        (p1_points > p2_points) ? printf("Player 1 wins!\n") : printf("Player 2 wins!\n");
    }
}

int count_points(string word)
{
    char letter;
    int points = 0;

    for (int i = 0, length = strlen(word); i < length; ++i)
    {
        letter = toupper(word[i]);
        if (letter >= 'A' && letter <= 'Z')
        {
            points += POINTS[letter - 'A'];
        }
    }
    return points;
}
