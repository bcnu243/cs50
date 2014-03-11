#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main (void)
{
    long long count = 0;
    printf ("Enter Credit Card Number: ");
    long long n = GetLongLong();
    
    if ((n >= 350000000000000 && n <= 359999999999999) || (n >= 370000000000000 && n <= 379999999999999))
    {
        printf ("AMEX\n");
    }
    
    else if ((n >= 5100000000000000 && n <= 5199999999999999) || (n >= 5200000000000000 && n <= 5299999999999999) || (n >= 5300000000000000 && n <= 5399999999999999) || (n >= 5400000000000000 && n <= 5499999999999999) || (n >= 5500000000000000 && n <= 5599999999999999))
    {
        printf ("MASTERCARD\n");
    }
    
    else if ((n >= 4000000000000 && n <= 4999999999999) || (n >= 4000000000000000 && n <= 4999999999999999))
    {
        printf ("VISA\n");
    }
    
    else
    {
        printf ("UNKNOWN CARD\n");
    }
    
    
    
    while(n)
    {
        n=n/10;
        count++;
    }
    printf("Digits: %lli\n", count);
    
    
}
