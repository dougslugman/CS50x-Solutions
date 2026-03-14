#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char characters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int score[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

string string1;
string string2;

int string1Score;
int string2Score;

void GetInputs()
{
    string i1 = get_string("Player 1: ");
    string i2 = get_string("Player 2: ");
    string1 = i1;
    string2 = i2;
}

void GetScore()
{
    int strSize1 = strlen(string1);
    int strSize2 = strlen(string2);
    int string1Sum = 0;
    int string2Sum = 0;
    int i, j, k;
    int charactersSize = sizeof(characters) / sizeof(characters[0]);
    for (i = 0; i < strSize1; i++)
    {
        for (k = 0; k < charactersSize; k++)
        {
            if (tolower(string1[i]) == characters[k])
            {
                string1Sum += score[k];
            }
        }
    }
    for (j = 0; j < strSize2; j++)
    {
        for (k = 0; k < charactersSize; k++)
        {
            if (tolower(string2[j]) == characters[k])
            {
                string2Sum += score[k];
            }
        }
    }
    string1Score = string1Sum;
    string2Score = string2Sum;
}

void CalcScore()
{
    if (string1Score > string2Score)
    {
        printf("Player 1 Wins!\n");
    }
    else if (string2Score > string1Score)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int main()
{
    GetInputs();
    GetScore();
    CalcScore();
    return 0;
}
