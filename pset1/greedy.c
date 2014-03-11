#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main (void)
{
    float change;
    change = 0;

    while (change <= 0)
    {
        printf ("Please enter the amount of change.\n");
        printf ("Change: ");
        change = GetFloat(); //Gets the Float from the user.
        if (change <= 0)
        {
            printf ("Retry: ");
            change = GetFloat(); //Gets the Float from the user.
        }
    }
    
    
    int cents = (int) round (change * 100); //Makes the input into an Integer so it can be calculated.
    
    int coins; //Initializes coins
    coins = 0;
    
    do
    {
        while (cents >= 25) //As long as the change is greater than or equal to 25 then it'll keep looping.
        {
            cents = cents - 25; //Subtracts 25 to the cents (change) variable.
            coins++; //Adds 1 to the coins variable.
        }
        while (cents >= 10) //As long as the change is greater than or equal to 10 then it'll keep looping.
        {
            cents = cents - 10; //Subtracts 10 to the cents (change) variable.
            coins++; //Adds 1 to the coins variable.
        }
        while (cents >= 5) //As long as the change is greater than or equal to 5 then it'll keep looping.
        {
            cents = cents - 5; //Subtracts 5 to the cents (change) variable.
            coins++; //Adds 1 to the coins variable.
        }
        while (cents >= 1) //As long as the change is greater than or equal to 1 then it'll keep looping.
        {
            cents = cents - 1; //Subtracts 1 to the cents (change) variable.
            coins++; //Adds 1 to the coins variable.
        }
    }
    while (cents < 0);
    
    printf("%i\n", coins);
}
