#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the letter frequency of a given text
void calculate_letter_frequency(const char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            frequency[index]++;
        }
    }
}

// Function to decrypt the ciphertext using the derived key
void decrypt_with_key(const char *ciphertext, const int *key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base_char = islower(ciphertext[i]) ? 'a' : 'A';
            int index = tolower(ciphertext[i]) - 'a';
            plaintext[i] = key[index] + base_char;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

// Function to find the most frequent letter in the text
int find_most_frequent_letter(const int *frequency) {
    int max_freq = 0;
    int max_index = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > max_freq) {
            max_freq = frequency[i];
            max_index = i;
        }
    }
    return max_index;
}

// Function to perform a letter frequency attack on the ciphertext
void letter_frequency_attack(const char *ciphertext, char *plaintext, char expected_most_frequent_letter) {
    int frequency[ALPHABET_SIZE] = {0};
    calculate_letter_frequency(ciphertext, frequency);
    int most_frequent_index = find_most_frequent_letter(frequency);
    
    // Calculate shift based on user-provided most frequent letter
    int shift = (most_frequent_index + ALPHABET_SIZE - (tolower(expected_most_frequent_letter) - 'a')) % ALPHABET_SIZE;
    int key[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = (i - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
    }

    decrypt_with_key(ciphertext, key, plaintext);
}

int main() {
    // User input for ciphertext
    char ciphertext[100];
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    // User input for expected most frequent letter
    char expected_most_frequent_letter;
    printf("Enter the most frequent letter you expect (e.g., 'e'): ");
    scanf(" %c", &expected_most_frequent_letter);

    char plaintext[100]; 
    letter_frequency_attack(ciphertext, plaintext, expected_most_frequent_letter);

    // Output the decrypted plaintext
    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}
