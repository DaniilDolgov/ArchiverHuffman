#ifndef ALICOMPRESSOR_COMPRESS_H
#define ALICOMPRESSOR_COMPRESS_H

#include <stdlib.h>
#include "tree_node.h"
#include "queue.h"
#include <stdint.h>
#include <string.h>

void encoding(node *root, const char *string, char **huff_code);
void add_node_decompressing(node* root, const char* code, char sym, int currentID);

node* build_tree_from_codes( char** huff_codes);

void huff_decompressing(const char* path_file);
void decoding(node* root, int* id, const char* string, FILE* file);
void create_huff_tree(const char* stroka);
void file_parsing(const char* path_file);

int getBit(unsigned char byte, int position);
int binToDec(unsigned char byte);

#endif