#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);

    int width = height * 2 + 2;
    int j;

    for (int i = 0; i < height; ++i)
    {
        j = 0;
        while (j < width - height + i + 1)
        {
            ((j >= height - i - 1) && (j < height)) || ((j >= height + 2) && (j <= width - height + i)) ? printf("#") : printf(" ");
            j++;
        }
        printf("\n");
    }
}
