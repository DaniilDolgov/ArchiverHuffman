#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "compress.h"

void firstMessage() {
    printf("Hello! My name is Daniel, and there is my project called 'Archiver' based on the Huffman Algorithm\n");
    printf("My program can compress and decompress the file\n");
    printf("\n");
    printf("1) If you want to compress the file, run the program with flag -c and provide the filename\n" 
           "For example, it might look like this: \"./program -c file.txt\" \n\n");
    printf("2) If you want to decompress the file, run the program with flag -d and provide the filename\n"
           "For example, it might look like this: \"./program -d file.huf\" \n\n");
}

int main(int argc, char** argv) {
    if (argc < 3) {
        firstMessage();
        return 1;
    }
    if (strcmp(argv[1], "-c") == 0) {
        FILE* file = fopen(argv[2], "r");
        if (file == NULL) {
            printf("this is not the right filename: %s", argv[2]);
            return 1;
        }
        fseek(file, 0L, SEEK_END);
        uint64_t position = ftell(file);
        rewind(file);
        char* string = (char*)malloc(sizeof(char) * position + 1);
        fread(string, position, sizeof(char), file);
        create_huff_tree(string);
        free(string);
        fclose(file);
    } 
    else if (!strcmp(argv[1], "-d"))
        huff_decompressing(argv[2]);
    else
        firstMessage();
    return 0;
}