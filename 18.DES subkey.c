#include <stdio.h>
#include <stdint.h>

// Permutation tables (IP, PC1, and PC2)
static const int IP[] = { 2, 6, 3, 1, 4, 8, 5, 7 };
static const int PC1[] = { 2, 4, 1, 6, 3, 9, 0, 8, 5, 7 };
static const int PC2[] = { 5, 2, 6, 3, 7, 4, 9, 8 };

// Function to perform permutation
uint64_t permute(uint64_t input, const int *table, int size) {
    uint64_t result = 0;
    for (int i = 0; i < size; i++) {
        result |= ((input >> (64 - table[i])) & 1) << (size - 1 - i);
    }
    return result;
}

// Function to generate subkeys
void generate_subkeys(uint64_t key, uint64_t *subkeys) {
 // 0x0000FFFFFFFFFFFF
    key = permute(key, PC1, 56);  // Apply PC1 to the key
    for (int i = 0; i < 5; i++) {  // Only generate 5 subkeys
        uint64_t shifted_key = (key << i) | (key >> (28 - i));  // Circular shift
        subkeys[i] = permute(shifted_key, PC2, 48);  // Apply PC2 to get subkey
    }
}

int main() {
    uint64_t subkeys[5];
    uint64_t key;

    // User input for key
    printf("Enter key in hexadecimal (e.g., 0x0000FFFFFFFFFFFF): ");
    scanf("%llx", &key);

    // Generate 5 subkeys
    generate_subkeys(key, subkeys);

    // Output the 5 generated subkeys
    printf("Generated Subkeys:\n");
    for (int i = 0; i < 5; i++) {
        printf("K%d: 0x%012llX\n", i + 1, subkeys[i]);
    }

    return 0;
}
