#include <stdio.h>
#include <string.h>

#define d 256 // Number of characters in the input alphabet

// Function to search for a pattern using the Rabin-Karp algorithm
void search(char pattern[], char text[]) {
    int M = strlen(pattern); // Length of the pattern
    int N = strlen(text);    // Length of the text
    int i, j;
    int p = 0; // Hash value for the pattern
    int t = 0; // Hash value for the current window of the text
    int h = 1; // Hash multiplier
    int q = 101; // A prime number to use as the modulo divisor

    // Calculate the hash multiplier: h = d^(M-1) % q
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash values of the pattern and the initial window of the text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the window one character at a time
    for (i = 0; i <= N - M; i++) {
        // Check if the hash values match
        if (p == t) {
            // Check if the characters match
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == M) // If pattern[0...M-1] = text[i...i+M-1]
                printf("Pattern found at index %d\n", i);
        }

        // Calculate the hash value for the next window of the text
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            if (t < 0) // Make sure t is positive
                t = (t + q);
        }
    }
}

// Main function
int main() {
    char text[] = "AABAACAADAABAAABAA";
    char pattern[] = "AABA";
    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);
    search(pattern, text);
    return 0;
}
