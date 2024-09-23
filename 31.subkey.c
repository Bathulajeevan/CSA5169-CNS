#include <stdio.h>
#include <string.h>

void leftShift(unsigned char *input, unsigned char *output, int block_size) {
    int carry = 0;
    for (int i = block_size - 1; i >= 0; --i) {
        output[i] = (input[i] << 1) | carry;
        carry = (input[i] & 0x80) ? 1 : 0;  // Save MSB for next byte
    }
}

void xorWithConstant(unsigned char *input, int block_size, int block_bits) {
    unsigned char constant = (block_bits == 128) ? 0x87 : 0x1B;
    input[block_size - 1] ^= constant;  // XOR with constant on the last byte
}

void generateSubkeys(unsigned char *blockCipherOutput, unsigned char *K1, unsigned char *K2, int block_size, int block_bits) {
    leftShift(blockCipherOutput, K1, block_size);

    // If MSB of blockCipherOutput is 1, XOR with the constant
    if (blockCipherOutput[0] & 0x80) {
        xorWithConstant(K1, block_size, block_bits);
    }

    // Derive K2 from K1
    leftShift(K1, K2, block_size);

    // If MSB of K1 is 1, XOR K2 with the constant
    if (K1[0] & 0x80) {
        xorWithConstant(K2, block_size, block_bits);
    }
}

int main() {
    int block_bits;
    int block_size;
    
    // Get block size from user
    printf("Enter block size (64 or 128 bits): ");
    scanf("%d", &block_bits);

    if (block_bits == 128) {
        block_size = 16;  // 128 bits = 16 bytes
    } else if (block_bits == 64) {
        block_size = 8;   // 64 bits = 8 bytes
    } else {
        printf("Invalid block size.\n");
        return 1;
    }

    unsigned char blockCipherOutput[16] = {0};  // Simulate an all-zero block cipher output
    unsigned char K1[16] = {0};  // First subkey
    unsigned char K2[16] = {0};  // Second subkey

    generateSubkeys(blockCipherOutput, K1, K2, block_size, block_bits);

    printf("K1: ");
    for (int i = 0; i < block_size; ++i) {
        printf("%02x", K1[i]);
    }
    printf("\nK2: ");
    for (int i = 0; i < block_size; ++i) {
        printf("%02x", K2[i]);
    }
    printf("\n");

    return 0;
}
