#include <cs50.h>
#include <stdio.h>

int main (void)
{
    for (int i = 65; i < 65 + 25; i++)
    {
        printf("%i is %c\n", i, (char) i);
    }
}
