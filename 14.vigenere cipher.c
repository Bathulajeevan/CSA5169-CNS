#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

// Function to convert a character to its numeric representation (0-25)
int charToNum(char c) {
    if (isalpha(c)) {
        return toupper(c) - 'A';
    }
    return -1; // Return -1 for non-alphabet characters
}

// Function to convert a number (0-25) to its corresponding uppercase character
char numToChar(int num) {
    return num + 'A';
}

// Function to encrypt plaintext using one-time pad Vigenère cipher
void encryptVigenere(char *text, int *keyStream, int keyLen) {
    int i;
    int textLen = strlen(text);
    for (i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            int shift = keyStream[i % keyLen];
            int num = charToNum(text[i]);
            num = (num + shift) % 26;
            text[i] = numToChar(num);
        }
    }
}

// Function to compute key stream from ciphertext and plaintext
void computeKeyStream(char *plaintext, char *ciphertext, int *keyStream) {
    int i;
    int textLen = strlen(plaintext);
    for (i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i]) && isalpha(ciphertext[i])) {
            int pNum = charToNum(plaintext[i]);
            int cNum = charToNum(ciphertext[i]);
            keyStream[i] = (cNum - pNum + 26) % 26; // Compute the key stream value
        } else {
            keyStream[i] = 0; // Handle non-alphabetic characters if necessary
        }
    }
}

int main() {
    char plaintext[MAX_LEN];
    char targetPlaintext[MAX_LEN];
    int keyStream[MAX_LEN];
    int computedKeyStream[MAX_LEN];
    int keyLen, i;

    // Input plaintext
    printf("Enter the plaintext (only letters): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    // Input key stream
    printf("Enter the number of key values: ");
    scanf("%d", &keyLen);
    if (keyLen <= 0 || keyLen > MAX_LEN) {
        printf("Invalid key length.\n");
        return 1;
    }

    printf("Enter the key values (space-separated): ");
    for (i = 0; i < keyLen; i++) {
        scanf("%d", &keyStream[i]);
        if (keyStream[i] < 0 || keyStream[i] >= 26) {
            printf("Key values must be between 0 and 25.\n");
            return 1;
        }
    }

    // Input target plaintext
    printf("Enter the target plaintext (only letters): ");
    getchar(); // Consume newline left by scanf
    fgets(targetPlaintext, sizeof(targetPlaintext), stdin);
    targetPlaintext[strcspn(targetPlaintext, "\n")] = '\0'; // Remove newline character

    // Encrypt plaintext with the given key stream
    char ciphertext[MAX_LEN];
    strcpy(ciphertext, plaintext); // Make a copy of plaintext for encryption
    encryptVigenere(ciphertext, keyStream, keyLen);
    printf("Encrypted text: %s\n", ciphertext);

    // Compute the key stream needed to decrypt the ciphertext to target plaintext
    if (strlen(targetPlaintext) == strlen(ciphertext)) {
        computeKeyStream(targetPlaintext, ciphertext, computedKeyStream);
        printf("Computed key stream: ");
        for (i = 0; i < strlen(targetPlaintext); i++) {
            printf("%d ", computedKeyStream[i]);
        }
        printf("\n");
    } else {
        printf("Error: Plaintext and target plaintext must have the same length.\n");
    }

    return 0;
}
