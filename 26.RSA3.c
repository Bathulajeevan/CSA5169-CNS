#include <stdio.h>
#include <math.h>

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
    long p, q, n, phi, e, d, message, encrypted, decrypted;

    // Input prime numbers p and q
    printf("Enter prime numbers p and q: ");
    scanf("%ld %ld", &p, &q);

    // Calculate n and phi(n)
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Input public key e
    printf("Enter public key e: ");
    scanf("%ld", &e);

    // Input private key d (this would be leaked in the scenario)
    printf("Enter private key d: ");
    scanf("%ld", &d);

    // Input message to encrypt
    printf("Enter message to encrypt: ");
    scanf("%ld", &message);

    // Encrypt the message
    encrypted = power_mod(message, e, n);
    printf("Encrypted message: %ld\n", encrypted);

    // Decrypt the message
    decrypted = power_mod(encrypted, d, n);
    printf("Decrypted message: %ld\n", decrypted);

    return 0;
}
