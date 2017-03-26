/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }
    
    // parse integer
    int n = atoi(argv[1]);
    if (n <= 0 || n >100){
        fprintf(stderr, "Usage: 0 < n <= 100\n");
        return 1;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }

    // store variables for old image information
    int oldHeight = bi.biHeight;
    int oldWidth = bi.biWidth;
    
    // resize the image bitmap file header & info header
    bi.biHeight *= n;
    bi.biWidth *= n;
    
    // calculate padding for old and new version of image
    int oldPad = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPad = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // calculate size image and file size
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPad) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < abs(oldHeight); i++)
    {
        // iterate over pixels in scanline n times
        for (int repeatV = 0; repeatV < n-1; repeatV++) {
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple to outfile n times
                for (int repeatH = 0; repeatH < n; repeatH++) {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                
            }
            // adding padding to new file
            for (int k = 0; k < newPad; k++)
            {
                fputc(0x00, outptr);
            }
            
            // offset to the current position to send the infile cursor back
            int offset = sizeof(RGBTRIPLE) * oldWidth;
            fseek(inptr, -offset, SEEK_CUR);
        }
        
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGB triple to outfile n times
            for (int repeatH = 0; repeatH < n; repeatH++) {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        
        // adding padding to new file
        for (int k = 0; k < newPad; k++)
        {
            fputc(0x00, outptr);
        }
        
        // skip over padding, if any
        fseek(inptr, oldPad, SEEK_CUR);
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
