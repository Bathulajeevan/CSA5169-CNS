#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

// Function to convert the string to lowercase
void toLowerCase(char plain[], int ps)
{
    for (int i = 0; i < ps; i++) {
        if (plain[i] >= 'A' && plain[i] <= 'Z')
            plain[i] += 32;
    }
}

// Function to remove all spaces in a string
int removeSpaces(char* plain, int ps)
{
    int count = 0;
    for (int i = 0; i < ps; i++)
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    plain[count] = '\0';
    return count;
}

// Function to generate the 5x5 key square
void generateKeyTable(char key[], int ks, char keyT[5][5])
{
    int dicty[26] = {0};
    int i = 0, j = 0;

    for (int k = 0; k < ks; k++) {
        if (key[k] != 'j' && dicty[key[k] - 'a'] == 0) {
            keyT[i][j] = key[k];
            dicty[key[k] - 'a'] = 1;
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    for (int k = 0; k < 26; k++) {
        if (dicty[k] == 0 && k != 9) { // Skip 'j'
            keyT[i][j] = 'a' + k;
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

// Function to search for the characters of a digraph in the key square
void search(char keyT[5][5], char a, char b, int arr[])
{
    if (a == 'j') a = 'i';
    if (b == 'j') b = 'i';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            } else if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

// Function to find the modulus with 5
int mod5(int a) { return (a % 5); }

// Function to make the plain text length even
int prepare(char str[], int ps)
{
    for (int i = 0; i < ps; i += 2) {
        if (str[i] == str[i + 1]) {
            memmove(&str[i + 1], &str[i], strlen(str) - i);
            str[i + 1] = 'x'; // Insert 'x' between same letters
            ps++;
        }
    }

    if (ps % 2 != 0) {
        str[ps++] = 'z'; // Add 'z' if the length is odd
        str[ps] = '\0';
    }

    return ps;
}

// Function for performing the encryption
void encrypt(char str[], char keyT[5][5], int ps)
{
    int a[4];

    for (int i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            // Same row
            str[i] = keyT[a[0]][mod5(a[1] + 1)];
            str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];
        } else if (a[1] == a[3]) {
            // Same column
            str[i] = keyT[mod5(a[0] + 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
        } else {
            // Rectangle swap
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Function to encrypt using Playfair Cipher
void encryptByPlayfairCipher(char str[], char key[])
{
    int ps, ks;
    char keyT[5][5];

    // Key
    ks = strlen(key);
    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    // Plaintext
    ps = strlen(str);
    toLowerCase(str, ps);
    ps = removeSpaces(str, ps);

    ps = prepare(str, ps);

    generateKeyTable(key, ks, keyT);

    encrypt(str, keyT, ps);
}

int main()
{
    char str[SIZE], key[SIZE];

    // Input key and plaintext from the user
    printf("Enter the key: ");
    fgets(key, SIZE, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the plaintext: ");
    fgets(str, SIZE, stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove trailing newline

    // Encrypt using Playfair Cipher
    encryptByPlayfairCipher(str, key);

    printf("Cipher text: %s\n", str);

    return 0;
}
