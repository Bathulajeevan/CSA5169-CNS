#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5 // 5x5 lanes for SHA-3

void initializeState(int state[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            state[i][j] = 0; // Initialize all lanes to zero
}

int allNonZero(int state[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (state[i][j] == 0) return 0; // Found a zero lane
    return 1; // All lanes have at least one nonzero bit
}

void randomSetBits(int state[SIZE][SIZE]) {
    int lane = rand() % SIZE;
    int bit = rand() % 64; // 64 bits in a lane
    state[lane][0] |= (1ULL << bit); // Set a random bit in a random lane
}

int main() {
    int state[SIZE][SIZE];
    int iterations = 0, max_attempts;

    printf("Enter the maximum number of attempts to set bits: ");
    scanf("%d", &max_attempts);

    srand(time(NULL)); // Seed random number generator
    initializeState(state);

    while (!allNonZero(state) && iterations < max_attempts) {
        randomSetBits(state);
        iterations++;
    }

    if (allNonZero(state)) {
        printf("Iterations before all lanes are nonzero: %d\n", iterations);
    } else {
        printf("Reached maximum attempts (%d) without filling all lanes.\n", max_attempts);
    }

    return 0;
}
