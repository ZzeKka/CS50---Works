#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // Ask user for a credit card number
    long credit_number = get_long("Number: ");
    long number = credit_number;
    int count = 0;
    int double_sum = 0, single_sum = 0;
    int digit_sum_number;

    // Storing sum in values while counting the credit card number digits
    while (number != 0)
    {
        if (count % 2 == 0)
        {
            single_sum += (number % 10);
        }
        else
        {
            digit_sum_number = (2 * (number % 10));
            while (digit_sum_number != 0)
            {
                double_sum = double_sum + (digit_sum_number % 10);
                digit_sum_number /= 10;
            }
        }
        number /= 10;
        count++;
    }

    // Check card type
    int final_sum = double_sum + single_sum;
    if (final_sum % 10 == 0)
    {
        if ((count == 13 || count == 16) && (credit_number / (long) pow(10, count - 1)) == 4)
        {
            printf("VISA\n");
        }
        else if (count == 16 && ((credit_number / (long) pow(10, count - 2)) >= 51) &&
                 ((credit_number / (long) pow(10, count - 2)) <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if (count == 15 &&
                 ((credit_number / (long) pow(10, count - 2)) == 34 || (credit_number / (long) pow(10, count - 2)) == 37))
        {
            printf("AMEX\n");
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
