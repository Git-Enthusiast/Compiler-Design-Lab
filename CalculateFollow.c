#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

// Arrays to store productions, FIRST and FOLLOW sets
char productions[MAX][MAX], first[MAX][MAX], follow[MAX][MAX], nonTerminals[MAX];
int n, followIndex[MAX] = {0};

// Function to find the index of a non-terminal
int findNonTerminalIndex(char c) {
    for (int i = 0; i < n; i++)
        if (nonTerminals[i] == c)
            return i;
    return -1;
}

// Function to find FIRST of a non-terminal
void findFirst(char c, int index) {
    for (int i = 0; i < n; i++) {
        if (productions[i][0] == c) {
            if (!isupper(productions[i][2])) {
                // Terminal
                first[index][followIndex[index]++] = productions[i][2];
            } else {
                // Non-terminal
                findFirst(productions[i][2], index);
            }
        }
    }
}

// Function to find FOLLOW of a non-terminal
void findFollow(char c) {
    if (productions[0][0] == c) {
        follow[findNonTerminalIndex(c)][followIndex[findNonTerminalIndex(c)]++] = '$'; // Start symbol
    }

    for (int i = 0; i < n; i++) {
        for (int j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == c) {
                if (productions[i][j + 1] != '\0') {
                    if (!isupper(productions[i][j + 1])) {
                        follow[findNonTerminalIndex(c)][followIndex[findNonTerminalIndex(c)]++] = productions[i][j + 1];
                    } else {
                        int idx = findNonTerminalIndex(productions[i][j + 1]);
                        for (int k = 0; k < followIndex[idx]; k++) {
                            follow[findNonTerminalIndex(c)][followIndex[findNonTerminalIndex(c)]++] = first[idx][k];
                        }
                    }
                } else {
                    // Recur for the non-terminal on LHS
                    findFollow(productions[i][0]);
                }
            }
        }
    }
}

int main() {
    int i, j;
    char choice;

    // Input number of productions
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    // Input the productions
    printf("Enter the productions (e.g., E=E+T or A=aB):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", productions[i]);
        nonTerminals[i] = productions[i][0];
    }

    // Initialize FIRST sets
    for (i = 0; i < n; i++) {
        findFirst(nonTerminals[i], i);
    }

    // Compute FOLLOW sets
    for (i = 0; i < n; i++) {
        findFollow(nonTerminals[i]);
    }

    // Output the FOLLOW sets
    for (i = 0; i < n; i++) {
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (j = 0; j < followIndex[i]; j++) {
            printf("%c ", follow[i][j]);
        }
        printf("}\n");
    }

    return 0;
}


/*
Enter the number of productions: 3
Enter the productions (e.g., E=E+T or A=aB):
E=E+T
E=T
T=T*F

FOLLOW(E) = { $ }
FOLLOW(T) = { + $ }
FOLLOW(F) = { * + $ }


*/