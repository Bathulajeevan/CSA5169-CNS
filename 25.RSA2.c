#include <stdio.h>

long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    long n, e, plaintext_block, factor;

    // Input n (product of primes p and q), e (public key), and plaintext block
    printf("Enter n (product of p and q): ");
    scanf("%ld", &n);
    printf("Enter public key e: ");
    scanf("%ld", &e);
    printf("Enter a plaintext block: ");
    scanf("%ld", &plaintext_block);

    // Compute GCD of plaintext block and n
    factor = gcd(plaintext_block, n);

    // Check if factor is non-trivial (i.e., greater than 1)
    if (factor > 1 && factor < n) {
        printf("Non-trivial factor found: %ld\n", factor);
        printf("The other factor of n is: %ld\n", n / factor);
    } else {
        printf("No common factor found.\n");
    }

    return 0;
}
