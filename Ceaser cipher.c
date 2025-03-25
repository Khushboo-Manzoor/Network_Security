#include <stdio.h>

void encryptCaesar(char message[], int shift) {
 
    for(int i = 0; message[i] != '\0'; ++i) {
        if(message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = (message[i] + shift - 'A') % 26 + 'A';
        }
        else if(message[i] >= 'a' && message[i] <= 'z') {
            message[i] = (message[i] + shift - 'a') % 26 + 'a';
        }
    }
}

int main() {
    char message[100];
    int shift;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter shift: ");
    scanf("%d", &shift);

    encryptCaesar(message, shift);

    printf("Encrypted message: %s\n", message);

    return 0;
}

Decryption:-
#include <stdio.h>

void decryptCaesar(char message[], int shift) {
    int i;
    for(i = 0; message[i] != '\0'; ++i) {
        if(message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = (message[i] - shift - 'A' + 26) % 26 + 'A';
        }
        else if(message[i] >= 'a' && message[i] <= 'z') {
            message[i] = (message[i] - shift - 'a' + 26) % 26 + 'a';
        }
    }
}

int main() {
    char message[100];
    int shift;

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter shift: ");
    scanf("%d", &shift);

    decryptCaesar(message, shift);

    printf("Decrypted message: %s\n", message);

    return 0;
}
