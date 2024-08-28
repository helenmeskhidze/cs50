#include <cs50.h>
#include <math.h>
#include <stdio.h>

int lengthofCC(long inputcc);
int checksum(long inputcc, int len);
int typeChecker(long inputcc, int len);

int main(void)
{
    long inputcc;
    inputcc = get_long("NUMBER: ");

    int len = lengthofCC(inputcc);
    int total = checksum(inputcc, len);

    if (total % 10 == 0)
    {
        // it passes checksum, determine what kind of card now with typeChecker
        int type = typeChecker(inputcc, len);
        if (type == 1)
        {
            printf("AMEX\n");
        }
        else if (type == 2)
        {
            printf("MASTERCARD\n");
        }
        else if (type == 3)
        {
            printf("VISA\n");
        }
        // passed checksum but none of the checked credit card types (shouldn't happen)
        else if (type == 0)
        {
            printf("INVALID\n");
        }
    }
    // didn't pass checksum
    else
    {
        printf("INVALID\n");
    }
}

int lengthofCC(long inputcc)
{
    // determine length of the CC number by dividing by powers of 10
    int len = 0;
    long remainder = inputcc;
    while (remainder > 10.0)
    {
        long lenpower = pow(10, len);
        remainder = inputcc / lenpower;
        len += 1;
    }
    return len;
}

int checksum(long inputcc, int len)
{
    // implement the checksum algorithm
    long sum = 0;
    long sumdouble = 0;
    for (int i = 1; i <= len; i += 2)
    {
        long powerupper = pow(10, i + 1);
        long power = pow(10, i);
        long powerlower = pow(10, i - 1);

        // digits
        int digit = ((inputcc % power) - ((inputcc % power) % powerlower)) / powerlower;
        int doubledigit = 2 * ((inputcc % powerupper) - ((inputcc % powerupper) % power)) / power;

        // add up the single digits
        sum += digit;
        // doubled digits can be more than 10; if so, add them seperately
        if (doubledigit >= 10)
        {
            int small = doubledigit % 10;
            int big = (doubledigit - (doubledigit % 10)) / 10;
            sumdouble += small;
            sumdouble += big;
        }
        else
        {
            sumdouble += doubledigit;
        }
    }

    long total = sum + sumdouble;
    return total;
}

int typeChecker(long inputcc, int len)
{
    int type = 0;
    // get the first digit and the first two digits
    long firstDigitpower = pow(10, len - 1);
    int firstDigit = inputcc / firstDigitpower;
    long firstTwoDigitspower = pow(10, len - 2);
    int firstTwoDigits = inputcc / firstTwoDigitspower;

    // Amex 15 digit and starts with 34 or 37
    if (len == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
    {
        type = 1;
    }
    // Mastercard is 16 digit and starts with something between 51 and 55
    else if (len == 16 && firstTwoDigits >= 51 && firstTwoDigits <= 55)
    {
        type = 2;
    }
    // Visa is 13 or 16 digits and starts with 4
    else if ((len == 13 || len == 16) && firstDigit == 4)
    {
        type = 3;
    }
    return type;
}
