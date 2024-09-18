#include <stdio.h>

#define ALPHABET_SIZE 26

// Function to find gcd of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to encrypt plaintext using affine cipher
char affineEncrypt(char p, int a, int b) {
    return (char)(((a * (p - 'A') + b) % ALPHABET_SIZE) + 'A');
}

// Function to decrypt ciphertext using affine cipher
char affineDecrypt(char c, int a, int b) {
    // Finding the modular inverse of a mod 26
    int a_inv = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if ((a * i) % ALPHABET_SIZE == 1) {
            a_inv = i;
            break;
        }
    }
    return (char)((a_inv * ((c - 'A') - b + ALPHABET_SIZE)) % ALPHABET_SIZE + 'A');
}

// Function to check allowed values of a
void checkAllowedValues() {
    printf("Allowed values of a:\n");
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (gcd(i, ALPHABET_SIZE) == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int a, b;
    char plaintext[100], ciphertext[100], decrypted[100];
    
    // Check allowed values of a
    checkAllowedValues();
    
    // Input values for encryption
    printf("Enter the value for a (allowed values from the list above): ");
    scanf("%d", &a);
    printf("Enter the value for b: ");
    scanf("%d", &b);
    printf("Enter the plaintext (uppercase only): ");
    scanf("%s", plaintext);
    
    // Encryption
    printf("Encrypted ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
        printf("%c", ciphertext[i]);
    }
    printf("\n");

    // Decryption
    printf("Decrypted plaintext: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decrypted[i] = affineDecrypt(ciphertext[i], a, b);
        printf("%c", decrypted[i]);
    }
    printf("\n");
    
    return 0;
}
