#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

char *CheckKey(string key)
{
    char checklist[26];
    int i, j, k, checklistsize;
    if (strlen(key) != 26)
    {
        return "Key must contain 26 characters.\n";
    }
    for (k = 0; k < 26; k++)
    {
        int checkalpha = isalpha(key[k]);

        if (checkalpha == 0)
        {
            return "Usage: ./substitution key\n";
        }
    }
    for (i = 0; i < 26; i++)
    {
        checklist[i] = key[i];
        for (j = 0; j < i; j++)
        {
            if (tolower(checklist[j]) == tolower(key[i]))
            {
                return "Key must not contain repeated characters.\n";
            }
        }
    }
    return "VALID";
}

void EncipherText(string key)
{
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext), i, j, k;
    bool check;
    char ciphertext[length];
    for (i = 0; i < length; i++)
    {
        check = false;
        for (j = 0; j < 26; j++)
        {
            if (tolower(plaintext[i]) == alphabet[j])
            {
                if (islower(plaintext[i]) > 0)
                {
                    ciphertext[i] = tolower(key[j]);
                }
                else
                {
                    ciphertext[i] = toupper(key[j]);
                }
                check = true;
            }
        }
        if (check == false)
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("ciphertext: ");
    for (k = 0; k < length; k++)
    {
        printf("%c", ciphertext[k]);
    }
    printf("\n");
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    char *checkkeyoutput = CheckKey(argv[1]);
    if (strcmp(checkkeyoutput, "VALID") != 0)
    {
        printf("\n%s", checkkeyoutput);
        return 1;
    }
    EncipherText(argv[1]);
    return 0;
}
