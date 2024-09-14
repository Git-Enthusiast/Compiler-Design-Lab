#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

void findFirst(char, int, int);
int count, n;
char calc_first[MAX][MAX];
char production[MAX][MAX], first[MAX];

// Function to find the FIRST of a non-terminal
void findFirst(char c, int q1, int q2) {
    int j;

    // If the symbol is a terminal, add it to the FIRST set
    if (!(isupper(c))) {
        calc_first[q1][q2++] = c;
    } else {
        for (j = 0; j < count; j++) {
            if (production[j][0] == c) {
                // If epsilon is present, look for alternatives
                if (production[j][2] == '#') {
                    if (production[q1][q2] == '\0')
                        calc_first[q1][q2++] = '#';
                    else if (production[q1][q2] != c)
                        findFirst(production[q1][q2], q1, q2);
                } else if (!isupper(production[j][2])) {
                    calc_first[q1][q2++] = production[j][2];
                } else {
                    findFirst(production[j][2], q1, q2);
                }
            }
        }
    }
}

int main() {
    int i, choice;
    char c, ch;

    // Read number of productions
    printf("Enter the number of productions: ");
    scanf("%d", &count);

    // Read the grammar productions
    for (i = 0; i < count; i++) {
        printf("Enter production %d: ", i + 1);
        scanf("%s", production[i]);
    }

    int k;
    char done[MAX];
    int ptr = -1;

    // Calculate FIRST sets for each non-terminal
    for (k = 0; k < count; k++) {
        c = production[k][0];
        int flag = 0;
        for (i = 0; i <= ptr; i++)
            if (c == done[i])
                flag = 1;

        if (flag == 1)
            continue;

        findFirst(c, k, 0);
        ptr += 1;

        // Store the processed non-terminal
        done[ptr] = c;
        printf("\nFIRST(%c) = { ", c);
        for (i = 0; i < strlen(calc_first[k]); i++) {
            printf("%c ", calc_first[k][i]);
        }
        printf("}\n");
    }
}

/*
Enter the number of productions: 6
Enter production 1: E->E+T
Enter production 2: E->T
Enter production 3: T->T*F
Enter production 4: T->F
Enter production 5: F->(E)
Enter production 6: F->id

FIRST(E) = { id ( }
FIRST(T) = { id ( }
FIRST(F) = { id ( }
  
*/