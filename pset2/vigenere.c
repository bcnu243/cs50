#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    if (argc != 2)//If user adds 2 or more additional arguments.
    {
        printf("Please enter one Alphabetical string argument.\n");
        return 1;
    }
    
    for (int i = 0, n = strlen(argv[1]); i < n; i++) //Checks each character to see if all are Alphabetical.
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Please enter only characters from the Alphabet please.\n");
            return 1;
        }
    }
    
    string p = GetString(); //Gets String from user.
    
    string k = argv[1]; //Takes the string 'argv[1]' and makes it a nicer looking string name.
    int length = strlen(k); //gets length of string 'k'.
    
    for (int i = 0, j = 0, n = strlen(p); i < n; i++)
    {
        
        int rotate = (k[j % length] >= 'A' && k[j % length] <= 'Z') ? ('A') : ('a'); // Create variable to convert "k" from ASCII to alpha val to be used to rotate the "p"
 
       
        if (isupper(p[i])) // If capitalized then.
        {
            int c = ((p[i] - 'A' + (k[j % length] - rotate)) % 26) + 'A'; // Convert the "p" from ASCII to alpha value, rotate according to key, convert back to ASCII
            printf("%c", c); // Print as ASCII value.
            j++; // Go to next letter in key word
        }
        
        
        else if (islower(p[i])) // If lower case then..
        {
            int cipher = ((p[i] - 'a' + (k[j % length] - rotate)) % 26) + 'a'; // Convert the char from ASCII to alpha value, rotate according to key, convert back to ASCII
            printf("%c", cipher); // Print as ASCII value.
            j++; // Go to next letter in key word
        }
        
        
        else // If char is not part of the alphabet, print as is
        {
            printf("%c", p[i]);
        } 
    }
    
    printf("\n"); //Prints new line to make things pretty.
        
       
    return 0;
    
}
