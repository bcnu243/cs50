#include <cs50.h>
#include <stdio.h>
#include <string.h>


int main (void)
{
    printf("Give a string.\n");
    string s = GetString();
    printf("%c\n", s[3]);
   
}
