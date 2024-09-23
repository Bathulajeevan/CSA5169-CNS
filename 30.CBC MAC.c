#include <stdio.h>
#include <string.h>

void xorBlocks(const char *input1, const char *input2, char *output, int block_size) {
    for (int i = 0; i < block_size; ++i) {
        output[i] = input1[i] ^ input2[i];
    }
}

void cbcMacOneBlock(const char *key, const char *message, char *mac, int block_size) {
    xorBlocks(key, message, mac, block_size);
}

void cbcMacTwoBlocks(const char *key, const char *message, char *mac, int block_size) {
    char t[block_size];
    cbcMacOneBlock(key, message, t, block_size);
    xorBlocks(message + block_size, t, mac, block_size);
}

int main() {
    int block_size = 8; 
    char key[block_size] = "abcdefgh"; // Hardcoded key
    char message[2 * block_size + 1]; // +1 for null terminator
    char mac[block_size];
    char macTwoBlocks[block_size];

    // Get user input for message
    printf("Enter a message (16 characters): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline character

    // Calculate MAC for one block
    cbcMacOneBlock(key, message, mac, block_size);
    printf("One-block MAC: ");
    for (int i = 0; i < block_size; ++i) {
        printf("%02x", (unsigned char)mac[i]);
    }
    printf("\n");

    // Calculate MAC for two blocks
    cbcMacTwoBlocks(key, message, macTwoBlocks, block_size);
    printf("Two-block MAC: ");
    for (int i = 0; i < block_size; ++i) {
        printf("%02x", (unsigned char)macTwoBlocks[i]);
    }
    printf("\n");

    return 0;
}
