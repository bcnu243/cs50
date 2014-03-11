#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    printf ("Please enter a key\n");
    int k = GetInt();
    printf ("Your key is: %i\n", k);
    
    printf ("Please enter a character\n");
    char c = GetChar();
    printf ("Your character is: %c\n", c);
    
    printf ("%c\n", c = (c + k));
    
    printf ("Input: ");
    string s = GetString();
    
    if (s != NULL)
    {
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            printf ("%c", s[i]);
        }
        printf ("\n");
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            printf ("%c", s[i]+k);
        }
        printf ("\n");
    }
     
}
