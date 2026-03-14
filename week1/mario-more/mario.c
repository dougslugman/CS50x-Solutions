#include <cs50.h>
#include <stdio.h>

int main()
{
    int i;
    int j;
    int k;
    int length = -1;

    do
    {
        length = get_int("Height: ");
    }

    while ((length <= 0) || (length >= 9));

    for (i = length; i > 0; i--)
    {
        int spaceNumber = i - 1;
        int hashNumber = (length - i) + 1;

        for (j = 0; j < spaceNumber; j++)
        {
            printf(" ");
        }

        for (k = 0; k < hashNumber; k++)
        {
            printf("#");
        }

        printf("  ");

        for (k = 0; k < hashNumber; k++)
        {
            printf("#");
        }

        printf("\n");
    }
    return 0;
}
