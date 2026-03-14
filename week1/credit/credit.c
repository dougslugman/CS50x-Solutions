#include <cs50.h>
#include <math.h>
#include <stdio.h>

long cardNumber;
int cardLength;

int NumberLength(long number)
{
    int count = 0;
    long length = 1;
    while (number >= length)
    {
        count++;
        length *= 10;
    }
    return count;
}

int GetDigit(long number, int digit)
{
    long divider = pow(10, digit - 1);
    long remainder = (number / divider) % 10;
    return remainder;
}

int CheckSum()
{
    int i;
    int j;
    int k;
    int sum = 0;
    cardNumber = get_long("Number: ");
    cardLength = NumberLength(cardNumber);

    for (i = 2; i <= cardLength; i += 2)
    {

        int cardDigit = (GetDigit(cardNumber, i) * 2);
        int cardDigitLength = NumberLength(cardDigit);
        for (j = 0; j < cardDigitLength; j++)
        {
            int cardDigitDigit = GetDigit(cardDigit, (j + 1));
            sum += cardDigitDigit;
        }
    }

    for (k = 1; k <= cardLength; k += 2)
    {
        int cardDigit = GetDigit(cardNumber, k);
        sum += cardDigit;
    }

    return ((sum % 10) == 0) ? 1 : 0;
}

char CheckCardType()
{

    int firstDigit = GetDigit(cardNumber, cardLength);
    int secondDigit = GetDigit(cardNumber, cardLength - 1);

    if ((cardLength == 15) && ((firstDigit == 3) && ((secondDigit == 4) || (secondDigit == 7))))
    {
        return 'A';
    }
    else if ((cardLength == 16) &&
             ((firstDigit == 5) &&
              ((secondDigit == 1) || (secondDigit == 2) || (secondDigit == 3) ||
               (secondDigit == 4) || (secondDigit == 5))))
    {
        return 'M';
    }
    else if (((cardLength == 13) || (cardLength == 16)) && (firstDigit == 4))
    {
        return 'V';
    }
    return 'I';
}

int main()
{
    int checkSumStatus = CheckSum();
    bool sumStatus = (checkSumStatus == 0) ? false : true;

    if (sumStatus == true)
    {
        char cardType = CheckCardType();
        if (cardType == 'A')
        {
            printf("AMEX\n");
        }
        else if (cardType == 'M')
        {
            printf("MASTERCARD\n");
        }
        else if (cardType == 'V')
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}
