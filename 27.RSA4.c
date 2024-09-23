#include <stdio.h>

// Function to calculate power mod n
long power_mod(long base, long exp, long n) {
    long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % n;
        }
        base = (base * base) % n;
        exp /= 2;
    }
    return result;
}

int main() {
    long e, n, message, encrypted;

    // Input public key e and modulus n
    printf("Enter public key e and modulus n: ");
    scanf("%ld %ld", &e, &n);

    // Input a message as a number (0-25 for A-Z)
    printf("Enter a message (0-25): ");
    scanf("%ld", &message);

    // Encrypt the message using RSA
    encrypted = power_mod(message, e, n);
    printf("Encrypted message: %ld\n", encrypted);

    return 0;
}
