#include <cs50.h>
#include <stdio.h>

int main (void)
{
    int h;
    
    do
    {
        printf ("Hello, welcome to Mario's Half Pyramid stacker.\n");
        printf ("How tall do we want the Half Pyramid to be from 0 to 23?\n");
        printf ("Height: ");
        h = GetInt(); //Gets the Int from the User.
        
        if (h < 0 || h > 23)
        {
            printf ("Retry: ");
            h = GetInt(); //Gets the Int from the User.
        }
    }
    while (h < 0 || h > 23);
    
    for (int i = 0; i < h; i++) //'i' will keep repeating this script till it is equal to 'h'.
    {
        for (int s = 0; (s + (i + 1)) < (h) ; s++) //'s' represents [space].
        {
            printf(" ");
        }
        
        for (int x = 0; x <= i; x++) //'x' respresents [#].
        {
            printf("#");
        }
        
        printf ("#"); //Adds the addition [#] to the pyramid.       
        
        printf ("\n"); //Adds new line.
        
    }
    
    
}
