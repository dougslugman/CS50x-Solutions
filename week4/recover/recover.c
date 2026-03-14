#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
    }
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("file not found\n");
        return 1;
    }
    uint8_t buffer[512];
    int count = 0;
    char *filename = malloc(sizeof(char) * 8);
    FILE *jpgptr = NULL;
    while (fread(buffer, sizeof(uint8_t), 512, card))
    {
        if (((buffer[0] == 0xff && buffer[1] == 0xd8) && buffer[2] == 0xff) &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", count);
            if (count != 0)
            {
                fclose(jpgptr);
            }
            jpgptr = fopen(filename, "w");
            count++;
        }
        if (count != 0)
        {
            fwrite(buffer, sizeof(uint8_t), 512, jpgptr);
        }
    }
    fclose(jpgptr);
    free(filename);
    fclose(card);
    return 0;
}
