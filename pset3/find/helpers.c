/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    
    int first = 0;
    int last = n-1;
    int middle = (first+last)/2;
    
    while (first <= last)
    {
        if (values[middle] < value )
            first = middle+1;
        else if (values[middle] > value)
            last = middle-1;
        else
            return true;
        middle = (first + last)/2;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for(int x=0; x<n; x++)

    {
		for(int y=0; y<n-1; y++)
		{
			if(values[y]>values[y+1])
			{
				int temp = values[y+1];
				values[y+1] = values[y];
				values[y] = temp;
			}
		}
	}
    return;
}
