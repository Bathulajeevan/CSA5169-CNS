#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void formatMessage(char *message, char *formatted) {
    int i, j = 0;
    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            formatted[j++] = toupper(message[i]);
        }
    }
    formatted[j] = '\0';
}

void findPosition(char letter, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == letter || (letter == 'J' && matrix[i][j] == 'I')) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char a, char b, char *cipherText) {
    int row1, col1, row2, col2;
    findPosition(a, &row1, &col1);
    findPosition(b, &row2, &col2);

    if (row1 == row2) {
        cipherText[0] = matrix[row1][(col1 + 1) % 5];
        cipherText[1] = matrix[row2][(col2 + 1) % 5];
    } else if (col1 == col2) {
        cipherText[0] = matrix[(row1 + 1) % 5][col1];
        cipherText[1] = matrix[(row2 + 1) % 5][col2];
    } else {
        cipherText[0] = matrix[row1][col2];
        cipherText[1] = matrix[row2][col1];
    }
}

void encryptMessage(char *message, char *cipherText) {
    char formatted[100];
    formatMessage(message, formatted);
    
    int len = strlen(formatted);
    int j = 0;

    for (int i = 0; i < len; i += 2) {
        if (i == len - 1 || formatted[i] == formatted[i + 1]) {
            encryptPair(formatted[i], 'X', &cipherText[j]);
            j += 2;
        } else {
            encryptPair(formatted[i], formatted[i + 1], &cipherText[j]);
            j += 2;
        }
    }
    cipherText[j] = '\0';
}

int main() {
    char message[100], cipherText[100];

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    encryptMessage(message, cipherText);

    printf("Encrypted Message: %s\n", cipherText);
    
    return 0;
}
