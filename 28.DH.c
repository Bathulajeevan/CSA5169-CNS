#include <stdio.h>

// Function to calculate power mod q
long power_mod(long base, long exp, long q) {
    long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % q;
        }
        base = (base * base) % q;
        exp /= 2;
    }
    return result;
}

int main() {
    long a, b, q, g, A, B, shared_secret;

    // Input public parameters
    printf("Enter prime number q and base g: ");
    scanf("%ld %ld", &q, &g);

    // Input secret numbers for Alice and Bob
    printf("Enter Alice's secret number a: ");
    scanf("%ld", &a);
    printf("Enter Bob's secret number b: ");
    scanf("%ld", &b);

    // Calculate A and B
    A = power_mod(g, a, q);
    B = power_mod(g, b, q);
    printf("Alice sends A = %ld\n", A);
    printf("Bob sends B = %ld\n", B);

    // Calculate shared secret
    shared_secret = power_mod(B, a, q);
    printf("Shared secret: %ld\n", shared_secret);

    return 0;
}
