#define _CRT_SECURE_NO_WARNINGS
#include "compress.h"

unsigned char byte_code(const char* B_code) {
    unsigned char res = 0;
    int len = strlen(B_code);
    for (int i = 0; i < len; ++i)
        if (B_code[i] == '1')
            res |= (1 << i);
    return res;
}

int getBit(unsigned char byte, int position) {
    if (byte & (1 << position))
        return 1;
    else
        return 0;
}

int binToDec(unsigned char byte) {
    int answer = 0;
    for (int i = 0; i < 8; ++i)
        answer = answer + (getBit(byte, i)) * (1 << i);
    return answer;
}

void decoding(node* root, int* id, const char* string, FILE* file) {
    if (root == NULL)
        return;
    if (!root->left && !root->right) {
        printf("%c", root->sym);
        fprintf(file, "%c", root->sym);
        return;
    }
    (*id)++;
    if (string[*id] == '0')
        decoding(root->left, id, string, file);
    else
        decoding(root->right, id, string, file);
}

void encoding(node *root, const char *string, char **huff_code) {
    if (root == NULL)
        return;
    if (!root->left && !root->right) {
        huff_code[(int) (root->sym)] = (char *)malloc(sizeof(char) * strlen(string) + 1);
        strcpy(huff_code[(int) (root->sym)], string);
    }
    char* left = (char*)malloc(sizeof(char) * strlen(string) + 2);
    strcpy(left, string);
    strcat(left, "0");
    encoding(root->left, left, huff_code);
    free(left);
    char* right = (char*)malloc(sizeof(char) * strlen(string) + 2);
    strcpy(right, string);
    strcat(right, "1");
    encoding(root->right, right, huff_code);
    free(right);
}

void add_node_decompressing(node *root, const char *code, char sym, int currentID) {
    if (currentID + 1 == strlen(code)) {
        if (code[currentID] == '1')
            root->right = build_the_node(sym, 1);
        else
            root->left = build_the_node(sym, 1);
    } 
    else {
        if (code[currentID] == '1') {
            if (root->right == NULL)
                root->right = build_the_node('\0', 0);
            add_node_decompressing(root->right, code, sym, currentID + 1);
        } 
        else {
            if (root->left == NULL)
                root->left = build_the_node('\0', 0);
            add_node_decompressing(root->left, code, sym, currentID + 1);
        }
    }
}

node *build_tree_from_codes(char **huff_codes) {
    node *root = build_the_node('\0', 0);
    for (int i = 0; i < 256; ++i)
        if (huff_codes[i] != NULL)
            add_node_decompressing(root, huff_codes[i], (char)i, 0);
    return root;
}

void create_huff_tree(const char* stroka) {
    const int alph_size = (1 << (sizeof(char) * 8));
    uint64_t* freq = (uint64_t*)calloc(alph_size, sizeof(uint64_t));
    for (uint64_t i = 0; i < strlen(stroka); ++i)
        ++freq[(int)stroka[i]];
    prior_queue* pr_queue = build_the_queue();
    int unique_cnt = 0;
    for (int i = 0; i < alph_size; ++i) {
        if (freq[i] > 0) {
            Insert(pr_queue, build_the_node((char)i, freq[i]));
            unique_cnt++;
        }
    }
    while (pr_queue->size != 1) {
        node* left = build_the_node(pr_queue->data[0]->sym, pr_queue->data[0]->freq);
        left->left = pr_queue->data[0]->left;
        left->right = pr_queue->data[0]->right;
        deleting_a_root(pr_queue, pr_queue->data[0]->sym);

        node* right = build_the_node(pr_queue->data[0]->sym, pr_queue->data[0]->freq);
        right->left = pr_queue->data[0]->left;
        right->right = pr_queue->data[0]->right;
        deleting_a_root(pr_queue, pr_queue->data[0]->sym);

        uint64_t sum = left->freq + right->freq;

        node* nodeNew = build_the_node('\0', sum);
        nodeNew->left = left;
        nodeNew->right = right;
        Insert(pr_queue, nodeNew);
    }
    node* root = pr_queue->data[0];
    char** huffman_code = (char**)calloc(alph_size + 1, sizeof(char*));
    encoding(root, "", huffman_code);
    FILE* encodedFile = fopen("encoded.zip", "wb");
    if (encodedFile == NULL) {
        printf("encoded file does not open");
        return;
    }
    fwrite(&unique_cnt, 1, 1, encodedFile);
    for (int i = 0; i < alph_size; ++i) {
        if (huffman_code[i] != NULL) {
            printf("%c: %s\n", (char)(i), huffman_code[i]);
            unsigned char len = strlen(huffman_code[i]);
            unsigned char symbol = (char)(i);
            unsigned char code = byte_code(huffman_code[i]);
            fwrite(&len, 1, 1, encodedFile);
            fwrite(&symbol, 1, 1, encodedFile);
            fwrite(&code, 1, 1, encodedFile);
        }
    }
    char* encoded = (char*)calloc(1000000, sizeof(char));
    for (int i = 0; i < strlen(stroka); ++i)
        strcat(encoded, huffman_code[(int)stroka[i]]);
    int offset = 8 - strlen(encoded) % 8;
    fwrite(&offset, 1, 1, encodedFile);
    for (int i = 0; i < strlen(encoded); i += 8) {
        unsigned char byte = 0;
        for (int j = 0; j < 8 && i + j < strlen(encoded); ++j)
            if (encoded[i + j] == '1')
                byte |= (1 << j);
        fwrite(&byte, 1, 1, encodedFile);
    }
    fclose(encodedFile);
    free(encoded);
    free(freq);
    deallocating_the_queue(pr_queue);
}

void file_parsing(const char *path_file) {
    FILE *file = fopen(path_file, "rb");
    const int alph_size = 256;
    char **huffman_code = (char**)calloc(alph_size + 1, sizeof(char *));
    unsigned char byte;
    fread(&byte, 1, 1, file);
    int unique_sym_cnt = binToDec(byte);
    printf("Unique symbols: %d\n", unique_sym_cnt);
    for (int i = 0; i < unique_sym_cnt; ++i) {
        fread(&byte, 1, 1, file);
        int length = binToDec(byte);
        printf("Length: %d\t", length);
        printf("\n");

        fread(&byte, 1, 1, file);
        unsigned char symb = byte;
        printf("Symbol: %c\n", byte);
        fread(&byte, 1, 1, file);
        printf("Code: ");
        char *code = (char*)calloc(9, sizeof(char));
        for (int i = length - 1, j = 0; i > -1; --i, ++j) {
            if (getBit(byte, i) == 1)
                code[i] = '1';
            else
                code[i] = '0';
        }
        printf("%s", code);
        huffman_code[(int)symb] = code;
        printf("\n\n");
    }
    node *root = build_tree_from_codes(huffman_code);
    unsigned char offsetByte;
    fread(&offsetByte, 1, 1, file);
    printf("Offset = %d\n", binToDec(offsetByte));

    char *encoded = (char*)calloc(1000000, 1);
    unsigned char sym;
    int i = 0;
    while (feof(file) == 0) {
        fread(&sym, 1, 1, file);
        for (int j = 0; j < 8; ++j) {
            if (getBit(sym, j) != 0)
                encoded[i++] = '1';
            else
                encoded[i++] = '0';
        }
    }
    encoded[strlen(encoded) - binToDec(offsetByte) - 8] = '\0';
    int idx = -1;
    printf("\nDecoded string is :\n");
FILE* rezult = fopen("decoded.txt", "w");
    while (idx < (int)strlen(encoded) - 1)
        decoding(root, &idx, encoded, rezult);
    fclose(rezult);
    free(encoded);
    for (int i = 0; i < alph_size; ++i)
        if (huffman_code[i] != NULL)
            free(huffman_code[i]);
    free(huffman_code);
    fclose(file);
}

void huff_decompressing(const char *path_file) {
    file_parsing(path_file);
}