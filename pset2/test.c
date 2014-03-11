#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main (int argc, string argv[])
{
        // if keyword does not meet requirement, print error and return 1
        if(argc != 2)
    {
        printf("Keyword must be only word, consisting of A-Z or a-z.\n");
        
        return 1;
    }       
    
    // if keyword contains any non-alphabetical char, print error and return 1
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
                printf("Keyword must be only word, consisting of A-Z or a-z.\n");
            
            return 1;
        }
    }
    
    // declare keyword and its length
    string k = argv[1];
    int length = strlen(k);
    
        // Once user submits an acceptable keyword prompt for plaintext
    string p = GetString();
        
        // Begin to encrypt and create variable "i" to keep track of plaintext and "j" for keyword position
        for (int i = 0, j = 0, n = strlen(p); i < n; i++)
    {
        // Create variable to convert "k" from ASCII to alpha val to be used to rotate the "p"
        int rotate = (k[j % length] >= 'A' && k[j % length] <= 'Z') ? ('A') : ('a');
 
        // If capitalized...
        if (p[i] >= 'A' && p[i] <= 'Z')
        {
            // Convert the "p" from ASCII to alpha val, rotate according to key, convert back to ASCII
            int cipher = ((p[i] - 'A' + (k[j % length] - rotate)) % 26) + 'A'; 
            
            // Print as ASCII val
            printf("%c", cipher);
            
            // Go to next letter in key word
            j++;
        }
        
        // If lower case...
        else if (p[i] >= 'a' && p[i] <= 'z')
        {
            // Convert the char from ASCII to alpha val, rotate according to key, convert back to ASCII
            int cipher = ((p[i] - 'a' + (k[j % length] - rotate)) % 26) + 'a';
            
            // Print as ASCII val
            printf("%c", cipher);
            
            // Go to next letter in key word
            j++;
        }
        
        // If char is not part of the alphabet, print as is
        else
        {
            printf("%c", p[i]);
        } 
    }
    
        // Print new line
        printf("\n");
        
        // Return 0 to signify no error
    return 0;
     
}
