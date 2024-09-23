#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALPHABET_SIZE 26

// Function to generate a random key for encryption
void generate_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE;
    }
}

// Function to perform Vigenère cipher encryption
void vigenere_encrypt(char *plaintext, int *key, char *ciphertext, int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = 'A' + (plaintext[i] - 'A' + key[i]) % ALPHABET_SIZE;
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = 'a' + (plaintext[i] - 'a' + key[i]) % ALPHABET_SIZE;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}

int main() {
    srand(time(0));

    // User input for plaintext
    char plaintext[100];
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character

    int length = strlen(plaintext);
    int key[length];
    char ciphertext[length + 1];

    // Generate random key and encrypt the plaintext
    generate_key(key, length);
    vigenere_encrypt(plaintext, key, ciphertext, length);

    // Print the results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
