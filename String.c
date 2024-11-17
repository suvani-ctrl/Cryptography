#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a string using the Shift Cipher
void encrypt(char input[], char output[], int key) {
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char offset = isupper(input[i]) ? 'A' : 'a';
            output[i] = ((input[i] - offset + key) % 26) + offset;
        } else {
            output[i] = input[i]; // Non-alphabetic characters remain unchanged
        }
    }
    output[i] = '\0'; // Null-terminate the output string
}

// Function to decrypt a string using the Shift Cipher
void decrypt(char input[], char output[], int key) {
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char offset = isupper(input[i]) ? 'A' : 'a';
            output[i] = ((input[i] - offset - key + 26) % 26) + offset;
        } else {
            output[i] = input[i]; // Non-alphabetic characters remain unchanged
        }
    }
    output[i] = '\0'; // Null-terminate the output string
}

// Function to perform brute-force decryption
void brute_force_decrypt(char input[]) {
    char decrypted[256];
    printf("\nBrute-force decryption results:\n");
    for (int key = 1; key <= 25; key++) {
        decrypt(input, decrypted, key);
        printf("Key %2d: %s\n", key, decrypted);
    }
}

int main() {
    char input[256], encrypted[256], decrypted[256];
    int key, choice;

    printf("Enter the text: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove the trailing newline character

    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    if (key < 1 || key > 25) {
        printf("Invalid key! Please enter a key between 1 and 25.\n");
        return 1;
    }

    printf("\nChoose an operation:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("3. Brute-force Decrypt\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            encrypt(input, encrypted, key);
            printf("Encrypted text: %s\n", encrypted);
            break;
        case 2:
            decrypt(input, decrypted, key);
            printf("Decrypted text: %s\n", decrypted);
            break;
        case 3:
            brute_force_decrypt(input);
            break;
        default:
            printf("Invalid choice! Exiting program.\n");
    }

    return 0;
}
