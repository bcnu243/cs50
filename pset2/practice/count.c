#include <cs50.h>
#include <stdio.h>

int main (void)
{
    int scores[5] = {1,2,3,4,5};
    
    for (int i = 0; i<5; i++)
    {
        printf("%d\n", scores[i]);
    }
}
