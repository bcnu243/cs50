/**
 * resize.c
 * by Bryon Urban
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP (Modified version of copy.c).
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    
    int n = 1;
    //change argument to an integer called n
    n = atoi(argv[1]);
    
    // if n is less than 0 or greater than 100 then...    
    if(n > 100 || n < 0)
    {
        printf("Usage: ./resize n infile outfile.\nn must be a positive integer from 0 to 100.\n");
        return 2;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    
    //Save Old Infile info and Update Current info
    //Old Width
    int oldWidth = bi.biWidth;
    bi.biWidth *= n;
    //Old Height
    int oldHeight = bi.biHeight;
    bi.biHeight *= n;
    
    
    // determine padding for scanlines
    int oldpadding =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;    
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    //new SizeImage info and Size of File
    bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * abs(bi.biHeight);
    bf.bfSize = 54 + bi.biWidth * abs(bi.biHeight) * 3 + abs(bi.biHeight) *  padding;
    
    int element;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));
    
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        element = 0;
    
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < n; k++)
            {
               *(buffer+(element)) = triple;
               element++;  
            }
        }

        // skip over padding, if any
        fseek(inptr, oldpadding, SEEK_CUR);


        // RGB triple to outfile
        for (int l = 0; l < n; l++)
        {
            fwrite((buffer), sizeof (RGBTRIPLE), bi.biWidth, outptr);
            
            // Padding to outfile
            for (int m = 0; m < padding; m++)
                fputc(0x00, outptr);
        }
    }
    
    // free memory
    free(buffer);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
