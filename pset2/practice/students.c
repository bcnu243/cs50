#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define NUMBER 5

int main (void)
{
    string names[NUMBER];
    for (int i = 0; i < NUMBER; i++)
    {
        printf("Name %d\n", i+1);
        names[i] = GetString();
    }
    srand(time(NULL));
    int name = rand() % NUMBER;
    printf("%s\n", names[name]);
}
