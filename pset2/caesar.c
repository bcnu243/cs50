#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (int argc, string argv[])
{
    if (argc != 2)//if user adds 2 or more additional arguments.
    {
        printf("Please enter one non-negative integer.\n");
        return 1;
    }
    int k = atoi(argv[1]);//Turns the argument from a string, to an int.
    if (k < 0)//if user inputs a negative argument.
    {
        printf("Please enter one non-negative integer.\n");
        return 1;
    }
    string p = GetString();//Gets string from user
    for (int i = 0, n = strlen(p); i<n; i++) //Loop till String Length.
    {
        if ((p[i] >= 'A' && p[i] <= 'Z') || (p[i] >= 'a' && p[i] <= 'z')) //If Char is within the alphabet then..
        {
            int c[i];
            c[i] = p[i]+k % 26; //Caesar Formula
            if ((c[i] > 'Z' && c[i] <= 'a') || c[i] > 'z' || c[i] <= 'A') //If Char is outside the alphabet after Formula then..
            {
                c[i] = c[i] - 26;
                printf("%c",c[i]);
            }
            else
            {
                printf("%c",c[i]);
            }
        }
        if ((p[i] < 'A') || (p[i] > 'z') || (p[i] > 'Z' && p[i] < 'a')) //If Char is outside the alphabet to begin with then..
        {
            printf("%c", p[i]);
        }
    }
    printf("\n"); //Prints new line to make things pretty.  
}
