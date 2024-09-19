#include <stdio.h>
#include <string.h>
#define SIZE 5
#define MAX_LEN 100

int main() {
    char key[MAX_LEN], cipher[MAX_LEN];
    char keyTable[SIZE][SIZE];
    int dict[26] = {0};  // To mark used characters
    int i, j, k = 0;
    int row1, col1, row2, col2;
    char decrypted[MAX_LEN];
    
    // Input key and cipher text
    printf("Enter key: ");
    fgets(key, MAX_LEN, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character if present

    printf("Enter cipher text (no spaces): ");
    fgets(cipher, MAX_LEN, stdin);
    cipher[strcspn(cipher, "\n")] = '\0'; // Remove newline character if present

    // Fill the key table with unique letters from the key
    for (i = 0; i < strlen(key); i++) {
        if (key[i] != 'j' && dict[key[i] - 'a'] == 0) {
            keyTable[k / SIZE][k % SIZE] = key[i];
            dict[key[i] - 'a'] = 1;
            k++;
        }
    }

    // Fill remaining letters
    for (i = 0; i < 26; i++) {
        if (i != 9 && dict[i] == 0) {
            keyTable[k / SIZE][k % SIZE] = 'a' + i;
            k++;
        }
    }

    // Decrypt the cipher text
    for (i = 0; i < strlen(cipher); i += 2) {
        // Find positions of the two characters
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (keyTable[r][c] == cipher[i]) {
                    row1 = r;
                    col1 = c;
                }
                if (keyTable[r][c] == cipher[i + 1]) {
                    row2 = r;
                    col2 = c;
                }
            }
        }

        if (row1 == row2) {
            decrypted[i] = keyTable[row1][(col1 + SIZE - 1) % SIZE];
            decrypted[i + 1] = keyTable[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            decrypted[i] = keyTable[(row1 + SIZE - 1) % SIZE][col1];
            decrypted[i + 1] = keyTable[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            decrypted[i] = keyTable[row1][col2];
            decrypted[i + 1] = keyTable[row2][col1];
        }
    }

    decrypted[strlen(cipher)] = '\0';
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
