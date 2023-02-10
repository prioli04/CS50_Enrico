#include <cs50.c>
#include <stdio.h>
#include <math.h>

bool checksum(long cred_n, int n_digits);

int main(void)
{
    // Get the credit card number
    long cred_n = get_long("Credit card number: ");

    // Get number of digits
    long mod = 10;
    int n_digits = 1;
    while (cred_n % mod != cred_n)
    {
        n_digits++;
        mod *= 10;
    }

    // Checking for a valid number
    bool is_valid = checksum(cred_n, n_digits);

    if (is_valid == false)
    {
        printf("INVALID\n");
    }
    else if (cred_n / pow(10, 12) < 1)// Discarding numbers that are too small
    {
        printf("INVALID\n");
    }
    else
    {
        // Determining the card brand
        int first_digit = (cred_n / pow(10, n_digits - 1));
        int second_digit = (cred_n / pow(10, n_digits - 2));
        second_digit = second_digit % 10;

        if (first_digit == 3)
        {
            if (second_digit == 4 || second_digit == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (first_digit == 4)
        {
            printf("VISA\n");
        }
        else if (first_digit == 5)
        {
            if (second_digit == 1 || second_digit == 2 || second_digit == 3 || second_digit == 4 || second_digit == 5)
            {
                printf("MASTERCARD\n");
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
    }

}

bool checksum(long cred_n, int n_digits)
{
    long current_digit;
    int sum1 = 0;
    int sum2 = 0;

    // Loop through each digit
    for (int i = 1; i <= n_digits; i++)
    {
        // Get current digit
        current_digit = cred_n % 10;
        cred_n /= 10;

        // Digit is in an odd position (Perform step 2 of the checksum algorithm)
        if (i % 2 != 0)
        {
            sum2 += current_digit;
        }
        else // Digit is in an even position (Perform step 1 of the checksum algorithm)
        {
            current_digit *= 2;
            if (current_digit < 10)
            {
                sum1 += current_digit;
            }
            else
            {
                sum1 += current_digit % 10;
                current_digit /= 10;
                sum1 += current_digit;
            }

        }

    }

    // Perform step 3 of the checksum algorithm
    int sum = sum1 + sum2;

    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}