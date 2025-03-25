#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to encrypt a message using Hill cipher
void encrypt(int key[2][2], char *message) {
    int len = strlen(message);

    // Pad the message with 'X' if its length is odd
    if (len % 2 != 0) {
        message[len] = 'X';
        message[len + 1] = '\0';
        len++;
    }

    for (int i = 0; i < len; i += 2) {
        int block[2] = {message[i] - 'A', message[i + 1] - 'A'};
        int result[2] = {0};

        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result[j] += key[j][k] * block[k];
            }
            result[j] %= 26;
        }

        message[i] = result[0] + 'A';
        message[i + 1] = result[1] + 'A';
    }
}

// Function to find the determinant of a 2x2 matrix
int determinant(int a, int b, int c, int d) {
    return a * d - b * c;
}

// Function to find the adjugate of a 2x2 matrix
void adjugate(int mat[2][2], int adj[2][2]) {
    adj[0][0] = mat[1][1];
    adj[0][1] = -mat[0][1];
    adj[1][0] = -mat[1][0];
    adj[1][1] = mat[0][0];
}

// Function to find the inverse of a 2x2 matrix
void inverse(int key[2][2], int inv[2][2]) {
    int det = determinant(key[0][0], key[0][1], key[1][0], key[1][1]);
    int modInv = modInverse(det, 26);

    if (det == 0 || modInv == -1) {
        printf("The matrix is not invertible modulo 26.\n");
        exit(1);
    }

    int adj[2][2];
    adjugate(key, adj);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            inv[i][j] = (adj[i][j] * modInv) % 26;
}

// Function to decrypt a message using Hill cipher
void decrypt(int key[2][2], char *message) {
    int inv[2][2];
    inverse(key, inv);

    int len = strlen(message);

    // Decrypt the message in blocks of 2
    for (int i = 0; i < len; i += 2) {
        int block[2] = {message[i] - 'A', message[i + 1] - 'A'};
        int result[2] = {0};

        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result[j] += inv[j][k] * block[k];
            }
            result[j] = (result[j] % 26 + 26) % 26;
        }

        message[i] = result[0] + 'A';
        message[i + 1] = result[1] + 'A';
    }
}

int main() {
    int key[2][2] = {
        {6, 24},
        {13, 16}
    };

    char message[] = "saim";

    printf("Original Message: %s\n", message);

    // Encrypt the message
    encrypt(key, message);
    printf("Encrypted Message: %s\n", message);

    // Decrypt the message
    decrypt(key, message);
    printf("Decrypted Message: %s\n", message);

    return 0;
}
