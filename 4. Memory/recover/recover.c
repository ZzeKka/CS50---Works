#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *memory_card = fopen(argv[1], "r");

    if (memory_card == NULL)
    {
        printf("Could not open file, Usage: ./recover card.raw.\n");
        return 1;
    }

    char *filename = malloc(sizeof(char) * 8);
    int image_count = 0;
    BYTE buffer[512];
    FILE *img = NULL;

    while (fread(buffer, sizeof(BYTE), 512, memory_card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", image_count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create file %s.\n", filename);
                free(filename);
                fclose(memory_card);
                return 1;
            }
            image_count++;
        }
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(memory_card);
    free(filename);
    return 0;
}
