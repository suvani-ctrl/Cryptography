#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8 // DES works on 64-bit blocks (8 bytes)
#define KEY_SIZE 8   // DES key size is 64 bits (8 bytes)

// A simple XOR-based "encryption" function for demonstration.
void xor_encrypt_decrypt(char *input, char *key, char *output, int length) {
    for (int i = 0; i < length; i++) {
        output[i] = input[i] ^ key[i % KEY_SIZE]; // XOR with key, cycling through it
    }
}

int main() {
    char plaintext[BLOCK_SIZE + 1]; // For 8-byte block size, +1 for null terminator
    char key[KEY_SIZE + 1];         // 8-byte key, +1 for null terminator
    char ciphertext[BLOCK_SIZE + 1];
    char decrypted[BLOCK_SIZE + 1];

    // Get plaintext input from user
    printf("Enter 8-character plaintext: ");
    fgets(plaintext, BLOCK_SIZE + 1, stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

    // Get key input from user
    printf("Enter 8-character key: ");
    fgets(key, KEY_SIZE + 1, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline

    // Check for valid input lengths
    if (strlen(plaintext) != BLOCK_SIZE || strlen(key) != KEY_SIZE) {
        printf("Error: Both plaintext and key must be exactly 8 characters.\n");
        return 1;
    }

    // Encrypt plaintext
    xor_encrypt_decrypt(plaintext, key, ciphertext, BLOCK_SIZE);
    ciphertext[BLOCK_SIZE] = '\0'; // Null-terminate the ciphertext

    printf("Ciphertext (hex): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decrypt ciphertext
    xor_encrypt_decrypt(ciphertext, key, decrypted, BLOCK_SIZE);
    decrypted[BLOCK_SIZE] = '\0'; // Null-terminate the decrypted text

    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
