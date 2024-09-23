#include <stdio.h>
#include <stdint.h>

#define DES_BLOCK_SIZE 8
#define DES_KEY_SIZE 8

void permute(uint64_t *data, const int *perm, int size) {
    uint64_t result = 0;
    for (int i = 0; i < size; i++) {
        result |= ((*data >> (64 - perm[i])) & 1) << (size - 1 - i);
    }
    *data = result;
}

uint64_t feistel(uint64_t half, uint64_t subkey) {
    return half ^ subkey;
}

void des_encrypt(uint64_t *data, uint64_t key) {
    uint64_t left = (*data >> 32) & 0xFFFFFFFF;
    uint64_t right = *data & 0xFFFFFFFF;
    for (int i = 0; i < 16; i++) {
        uint64_t temp = right;
        right = feistel(right, key);
        left ^= right;
        right = temp;
    }
    *data = (left << 32) | right;
}

void des_decrypt(uint64_t *data, uint64_t key) {
    uint64_t left = (*data >> 32) & 0xFFFFFFFF;
    uint64_t right = *data & 0xFFFFFFFF;
    for (int i = 15; i >= 0; i--) {
        uint64_t temp = left;
        left = feistel(left, key);
        right ^= left;
        left = temp;
    }
    *data = (right << 32) | left;
}

int main() {
    uint64_t key, plaintext, ciphertext;

    // User input for key and plaintext
    printf("Enter a 64-bit key (in hexadecimal, e.g., 0x12345678ABCDEF01): ");
    scanf("%llx", &key);

    printf("Enter a 64-bit plaintext (in hexadecimal, e.g., 0x0123456789ABCDEF): ");
    scanf("%llx", &plaintext);

    // Encrypting the plaintext
    ciphertext = plaintext;
    des_encrypt(&ciphertext, key);
    printf("Ciphertext: %016llx\n", ciphertext);

    // Decrypting the ciphertext
    des_decrypt(&ciphertext, key);
    printf("Decrypted: %016llx\n", ciphertext);

    return 0;
}
