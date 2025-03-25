#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereEncrypt(char *plaintext, const char *key) {
    int keyLength = strlen(key);

    for (int i = 0, j = 0; i < strlen(plaintext); ++i) {
        char currentChar = plaintext[i];


        if (isalpha(currentChar)) {
            char caseOffset = isupper(currentChar) ? 'A' : 'a';
            int shift = toupper(key[j % keyLength]) - 'A';

            plaintext[i] = (currentChar - caseOffset + shift) % 26 + caseOffset;

            ++j;
        }
    }
}

int main() {
    char plaintext[100];
    char key[100];

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    printf("Enter the key: ");
    scanf("%s", key);

    for (int i = 0; i < strlen(key); ++i) {
        if (!isalpha(key[i])) {
            printf("Invalid key!\n");
            return 1;
        }
    }

    vigenereEncrypt(plaintext, key);

    printf("\nEncrypted Text: %s\n", plaintext);

    return 0;
}
