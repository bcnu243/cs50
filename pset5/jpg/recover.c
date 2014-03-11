/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 *
 * Recovers JPEGs from a forensic image.
 * by Bryon Urban with help of Google, and of course, the CS50 Team.
 */
 #include <stdio.h>
 #include <stdint.h>
 
 const int BLOCK = 512; //Since #define BLOCK 512 didn't work, I googled this and it works!
 
 int main(int argc, char *agrv[])
 {
    FILE* inptr = fopen("card.raw", "r"); //Opens card.raw as readable
    
    if ((inptr = fopen("card.raw", "r")) == NULL)
    {
        printf("Failed to open file >:(\n");
        return 1;
    }
    
    uint8_t buffer[512]; //Creates a buffer the size of 512 bytes.
    
    int i = 0;
    FILE *outptr = NULL;
    
    // Iterate over file contents
    while (fread(buffer, BLOCK, 1, inptr))
    {
        // Check if the first four bytes are a JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // Close the file, if it is opened
            if (outptr != NULL)
                fclose(outptr);
            
            char filename[8];
            sprintf(filename, "%03d.jpg", i);
                
            // Open a new JPEG file for writing
            outptr = fopen(filename, "w");
            
            i++;
        }
        
        if (outptr != NULL)
            fwrite(buffer, BLOCK, 1, outptr);
    }
    
    if (outptr != NULL)
        fclose(outptr);
    
    fclose(inptr);
 
    return 0;
 } 
