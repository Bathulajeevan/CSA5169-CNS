#include <stdio.h>
#include <stdint.h>

// Initial Permutation (IP) and Inverse IP (IP_INV) tables
static const int IP[] = { 2, 6, 3, 1, 4, 8, 5, 7 };
static const int IP_INV[] = { 4, 1, 3, 5, 7, 2, 8, 6 };

// Function to perform permutation
uint64_t permute(uint64_t input, const int *table, int size) 
{
    uint64_t result = 0;
    for (int i = 0; i < size; i++) 
    {
        result |= ((input >> (64 - table[i])) & 1) << (size - 1 - i);
    }
    return result;
}
// DES decryption function

 //0x0123456789ABCDEF

uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) 
{
    uint64_t permuted_ciphertext = permute(ciphertext, IP, 64);
    uint64_t decrypted = permuted_ciphertext ^ key;
    decrypted = permute(decrypted, IP_INV, 64);
    return decrypted;
}

int main() 
{
    uint64_t ciphertext, key;

    // Take user input for ciphertext and key
    printf("Enter ciphertext in hexadecimal (e.g., 0x0123456789ABCDEF): ");
    scanf("%llx", &ciphertext);

    printf("Enter key in hexadecimal (e.g., 0x133457799BBCDFF1): ");
    scanf("%llx", &key);

    // Perform DES decryption
    uint64_t decrypted = des_decrypt(ciphertext, key);

    // Output results
    printf("Ciphertext: 0x%016llX\n", ciphertext);
    printf("Decrypted: 0x%016llX\n", decrypted);

    return 0;
}
