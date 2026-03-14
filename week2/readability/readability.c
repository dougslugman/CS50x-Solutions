#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char enders[] = {'.', '!', '?'};
    string text = get_string("Text: ");
    int textlength = strlen(text);
    int enderslength = (sizeof(enders) / sizeof(enders[0]));
    int i = 0, j = 0, wordcount = 0, lettercount = 0, sentencecount = 0;
    wordcount++;
    for (i = 0; i < textlength; i++)
    {
        if (isalpha(text[i]))
        {
            lettercount++;
        }

        if (text[i] == ' ')
        {
            wordcount++;
        }

        for (j = 0; j < enderslength; j++)
        {
            if (text[i] == enders[j])
            {
                sentencecount++;
            }
        }
    }

    double ratio = (100.0 / wordcount);
    double L = (lettercount * ratio);
    double S = (sentencecount * ratio);
    double grade = (0.0588 * L - 0.296 * S - 15.8);
    grade = round(grade);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("\nGrade %.0f\n", grade);
    }
    return 0;
}
