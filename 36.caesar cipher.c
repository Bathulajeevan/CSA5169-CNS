#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to perform affine encryption
int affine_encrypt(int a, int b, char p) {
    if (p >= 'A' && p <= 'Z') {
        return (a * (p - 'A') + b) % ALPHABET_SIZE + 'A';
    }
    return p;
}

// Function to encrypt the entire message using affine cipher
void encrypt_message(char *plaintext, int a, int b, char *ciphertext) {
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = affine_encrypt(a, b, plaintext[i]);
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    // User input for plaintext
    char plaintext[100];
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character

    // User input for affine cipher parameters a and b
    int a, b;
    printf("Enter value for 'a': ");
    scanf("%d", &a);
    printf("Enter value for 'b': ");
    scanf("%d", &b);

    // Encrypt the plaintext using the affine cipher
    char ciphertext[sizeof(plaintext)];
    encrypt_message(plaintext, a, b, ciphertext);

    // Print the results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
