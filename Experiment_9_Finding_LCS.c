#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

// Function to find the longest common subsequence
char* longestCommonSubsequence(char* X, char* Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int L[m + 1][n + 1];

    // Step 1: Initialize table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    // Step 2: Trace back to construct the longest common subsequence
    int index = L[m][n];
    char* lcs = (char*)malloc((index + 1) * sizeof(char));
    lcs[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    return lcs;
}

int main() {
    char X[MAX_LENGTH], Y[MAX_LENGTH];

    printf("Enter the first sequence: ");
    scanf("%s", X);

    printf("Enter the second sequence: ");
    scanf("%s", Y);

    char* lcs = longestCommonSubsequence(X, Y);

    printf("Longest Common Subsequence: %s\n", lcs);

    free(lcs);

    return 0;
}
