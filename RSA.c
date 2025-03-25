#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long power(long long base, long long expo, long long m) { 
    long long res = 1;
    base = base % m;
    while (expo > 0) {
        if (expo & 1)
            res = (res * base) % m; 
        base = (base * base) % m;
        expo = expo / 2;
    }
    return res;
}
)
int modInverse(int e, int phi) {
    for (int d = 2; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void generateKeys(int *e, int *d, int *n) {
    int p = 7919; 
    int q = 1009;

    *n = p * q;
    int phi = (p - 1) * (q - 1);

    for (*e = 2; *e < phi; (*e)++) {
        if (gcd(*e, phi) == 1)
            break;
    }

    *d = modInverse(*e, phi);
    if (*d == -1) {
        printf("Modular inverse does not exist. Choose different primes.\n");
        exit(1);
    }
}

void encrypt(char *message, int e, int n, long long *ciphertext) {
    int message_len = strlen(message);
    for (int i = 0; i < message_len; i++) {
        ciphertext[i] = power(message[i], e, n);
    }
}

void decrypt(long long *ciphertext, int ciphertext_len, int d, int n, char *decrypted_message) {
    for (int i = 0; i < ciphertext_len; i++) {
        decrypted_message[i] = (char)power(ciphertext[i], d, n);
    }
    decrypted_message[ciphertext_len] = '\0';
}

int main() {
    int e, d, n;

    generateKeys(&e, &d, &n);

    printf("Public Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    char message[100];
    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; 
    int message_len = strlen(message);

    long long *ciphertext = (long long *)malloc(message_len * sizeof(long long));
    char *decrypted_message = (char *)malloc((message_len + 1) * sizeof(char));

    if (ciphertext == NULL || decrypted_message == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    encrypt(message, e, n, ciphertext);

    printf("Encrypted Message: ");
    for (int i = 0; i < message_len; i++) {
        printf("%lld ", ciphertext[i]);
    }
    printf("\n");

    decrypt(ciphertext, message_len, d, n, decrypted_message);

    printf("Decrypted Message: %s\n", decrypted_message);

    free(ciphertext);
    free(decrypted_message);

    return 0;
}
