#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generateCipherSequence(const char *keyword, char cipher[ALPHABET_SIZE]) {
    int used[ALPHABET_SIZE] = {0}; // Array to track used letters
    int index = 0;

    // Add letters from the keyword to the cipher sequence
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (isalpha(ch) && !used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1; // Mark this letter as used
        }
    }

    // Add remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
}

void encrypt(const char *plaintext, const char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            ciphertext[i] = cipher[ch - 'A']; // Map plaintext letter to ciphertext
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate
}

void decrypt(const char *ciphertext, const char *cipher, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (cipher[j] == ch) {
                    plaintext[i] = 'A' + j; // Map ciphertext letter back to plaintext
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate
}

int main() {
    char keyword[100];
    char plaintext[100];

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline

    char cipher[ALPHABET_SIZE];
    generateCipherSequence(keyword, cipher);

    printf("Cipher Sequence: ");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", cipher[i]);
    }
    printf("\n");

    char ciphertext[strlen(plaintext) + 1];
    encrypt(plaintext, cipher, ciphertext);
    
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    char decryptedText[strlen(ciphertext) + 1];
    decrypt(ciphertext, cipher, decryptedText);
    
    printf("Decrypted Text: %s\n", decryptedText);
    
    return 0;
}
