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
    
    printf("Please enter a string of text to cipher\n");
    string p = GetString();//Gets string from user
    
    for (int i = 0, n = strlen(p); i<n; i++)
    {
        
        if (p[i] >= 'A' && p[i] <= 'Z' || p[i] >= 'a' && p[i] <= 'z')
        {
            int c[i];
            c[i] = p[i]+k % 26;
            printf("%c",c[i]);
        }
        if ((p[i] < 'A') || (p[i] > 'z') || (p[i] > 'Z' && p[i] < 'a'))
        {
            printf("%c", p[i]);
        }
        
        int c[i];
        if (c[i] > 'z' || (c[i] > 'Z' && c[i] < 'a') || c[i] < 'A')
        {
            c[i] = c[i] - 26;
            printf("%c",c[i]);
        }
        c[i] = p[i]+k % 26;
        if (c[i] > 'z' || (c[i] > 'Z' && c[i] < 'a') || c[i] < 'A')
        {
            c[i] = c[i] - 26;
        }
        
        printf("%c",c[i]);
        
        
        
    }
    printf("\n");    

}
