#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define UPPER_TO_ALPHA 65
#define LOWER_TO_ALPHA 97
#define ALPHA_LENGTH 26

int convertToAlphaIndex(int asciiIndex);
int convertToAsciiIndex(int alphaIndex, int checkUpper);

int main(int argc, string argv[])
{
    // check number of argument count
    if (argc != 2){
        printf("Usage: ./vigenere string\n");
        return 1;
    }
    
    // check if the second argument contain only character
    string key = argv[1];
    for (int i = 0; i<strlen(key); i++){
        if (!isalpha(key[i])){
            printf("Usage: ./vigenere string\n");
            return 1;
        }
    }
    
    // get string input
    printf("plaintext: ");
    string plaintext = get_string();
    
    printf("ciphertext: ");
    
    // letterNum keep track of position of letter count, start from 0
    int letterNum = 0;
    for (int i = 0; i<strlen(plaintext); i++){
        if isalpha(plaintext[i]){
            // c = (p + k) mod 26 
            // Convert both p & k to Alphabet Index, follow cipher rules then return ASCII index
            int p = convertToAlphaIndex(plaintext[i]);
            int keyIndex = letterNum % strlen(key);
            int k = convertToAlphaIndex(key[keyIndex]);
            int c = (p + k) % ALPHA_LENGTH;
            
            int cipherAscii = convertToAsciiIndex(c, plaintext[i]);
            printf("%c", (char)cipherAscii);
            letterNum++;
        } else {
            printf("%c",(char)plaintext[i]);
        }
        
    }
    printf("\n");
    return 0;
}

int convertToAlphaIndex(int asciiIndex){
    int alphaIndex;
    if isupper(asciiIndex){
        alphaIndex = asciiIndex - UPPER_TO_ALPHA;
    } else {
        alphaIndex = asciiIndex - LOWER_TO_ALPHA;
    }
    return alphaIndex;
}

int convertToAsciiIndex(int alphaIndex, int letterCase){
    int asciiIndex;
    if isupper(letterCase){
        asciiIndex = alphaIndex + UPPER_TO_ALPHA;
    } else {
        asciiIndex = alphaIndex + LOWER_TO_ALPHA;
    }
    return asciiIndex;
}