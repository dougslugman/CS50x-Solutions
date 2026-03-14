#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
const int HEADER_SIZE = 44;
void ptrnull(void *ptr)
{
    (ptr == NULL) ? exit(0) : NULL;
}
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    float factor = atof(argv[3]);

    for (int i = 0; i < HEADER_SIZE; i++)
    {
        char byte = fgetc(input);
        fputc(byte, output);
    }
    int16_t *sample = malloc(sizeof(int16_t));
    ptrnull(sample);
    printf("passed!\n");
    while (fread(sample, sizeof(int16_t), 1, input))
    {
        *sample *= factor;
        fwrite(sample, sizeof(int16_t), 1, output);
    }
    free(sample);
    fclose(input);
    fclose(output);
}
