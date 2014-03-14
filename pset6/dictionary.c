/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

#define SIZE 100

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

node* array[SIZE];
    
int lSize = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // string to hold lowercase  word
    char str[LENGTH + 1];

    // convert string to lowercase to check against out dictionary
    for(int i = 0; i < strlen(word); i++)
    {   
        if(word[i] == '\'')
            str[i] = '\'';
        else if(word[i] >= 'A' && word[i] <= 'Z')
            str[i] = (word[i] - 'A' + 'a');
        else
            str[i] = word[i];
    }
    str[strlen(word)] = '\0';
    // hash of word we're looking for 
    int index = (str[0] - 'a' + 33)%SIZE;
    
    // pointer to current node
    node *bucket = array[index];
    
    // traverse dictionary while next is not null 
    while(bucket->next != NULL)
    {
        if(strcmp(str, bucket->word) == 0)
            return true;
        bucket = bucket->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    /* Loads the dictionary into Memory */
    FILE *fp = fopen(dictionary, "r");
    if(fp == NULL)
    {
        printf("Error loading dictionary!\n");
        return 1;
    }

    /* Going through the global array, setting pointers up */
    int i = 0;
    while (i < SIZE)
    {
        array[i] = malloc(sizeof(node));
        array[i]->next = NULL;
        i++;
    }

    /* Get the word so it can be added to the dictionary */
    char key[LENGTH];
    int c;
    int index;
    int j = 0;

    /* While we have input add it to key */
    while((c = fgetc(fp)) != EOF)
    {
        if(c == '\n')
        {   
            key[j] = '\0';
            j = 0;
            index = (key[0] - 'a' + 33)%SIZE; // Hash key to get the array index where we will have our buckets.
            node *conductor = array[index]; // Store pointer to array to keep track out our position while we search
        
            /* Traverse the buckets looking for our key */
            if(conductor != NULL)
                while(conductor->next != NULL)
                    conductor = conductor->next;
                    
            /* If the key was not found, add a new bucket and put it to the top of our list */
            node *new_node = malloc(sizeof(node));
            strcpy(new_node->word, key);
            new_node->next = array[index];
            array[index] = new_node;
            
            /* 1-up the size of dictionary */
            lSize++;
        }
        else
        {   
            if(c == '\'')
                key[j] = '\'';
            else if(isupper(c))
                key[j] = tolower(c);
            else
                key[j] = (char)c;
            j++;
        }
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return lSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    /* Unloads list from Top to bottom. */
    node *bucket, *previous;
    int index = 0;
    while(index < SIZE)
    {
        bucket = array[index];
        while(bucket->next != NULL)
        {
            previous = bucket;
            bucket = bucket->next;
            free(previous);
        }
        index++;
        free(bucket);
       
    }
    return true;
}
