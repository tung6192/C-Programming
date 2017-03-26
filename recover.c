#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#define BLOCK 512


//global variables
int fileNum = 0;
char fileName[7];
FILE* outfile;

int main(int argc, char *argv[]){
    // check number of arguments
    if (argc !=2) {
        fprintf(stderr, "Usage: ./recover infile \n");
        return 1;
    }
    
    // open the card
    char *infile = argv[1];
    FILE *card = fopen(infile, "r");
    if (card == NULL) {
        fprintf(stderr, "Couldn't open the file \n");
        return 2;
    }
    
    // define a struct
    unsigned char buffer[BLOCK];
    
    // check end of the file
    while (fread(&buffer, 1, BLOCK, card) == BLOCK) {
        // check if it is jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            // close output file if this isn't the first jpeg
            if (fileNum != 0) {
                fclose(outfile);
            }
            sprintf(fileName, "%.3i.jpg", fileNum);
            outfile = fopen(fileName, "w");
            fwrite(&buffer, 1, BLOCK, outfile);
            fileNum++;
        } else {
            // continue write if haven't found any jpeg file
            if (fileNum != 0){
                fwrite(&buffer, 1, BLOCK, outfile);
            }
        }
    }
    fclose(outfile);
    

}