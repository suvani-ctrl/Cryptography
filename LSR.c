#include <stdio.h>
#include <string.h>

#define POLYNOMIAL 0xB8  // Example feedback polynomial: 10111000
#define LFSR_SEED 0xAC    // Initial seed for the LFSR

// Function to generate the next bit using LFSR
unsigned char lfsr_next_bit(unsigned char *lfsr) {
    unsigned char feedback = *lfsr & 1; // Get the least significant bit (LSB)
    if (feedback) {
        *lfsr = (*lfsr >> 1) ^ POLYNOMIAL; // Apply the polynomial if feedback bit is 1
    } else {
        *lfsr >>= 1; // Just shift if feedback bit is 0
    }
    return feedback;
}

// Function to generate a key stream using the LFSR
void generate_keystream(unsigned char *keystream, size_t length, unsigned char seed) {
    unsigned char lfsr = seed;
    for (size_t i = 0; i < length; i++) {
        keystream[i] = 0;
        for (int bit = 0; bit < 8; bit++) {
            keystream[i] |= lfsr_next_bit(&lfsr) << bit;
        }
    }
}

// Function to perform XOR operation for encryption/decryption
void xor_encrypt_decrypt(const char *input, char *output, const unsigned char *keystream, size_t length) {
    for (size_t i = 0; i < length; i++) {
        output[i] = input[i] ^ keystream[i];
    }
    output[length] = '\0'; // Null-terminate the string
}

int main() {
    char plaintext[256];
    printf("Enter plaintext (max 255 characters): ");
    fgets(plaintext, sizeof(plaintext), stdin);

    size_t text_length = strlen(plaintext);
    if (plaintext[text_length - 1] == '\n') {
        plaintext[text_length - 1] = '\0'; // Remove newline character
        text_length--;
    }

    unsigned char keystream[256];
    generate_keystream(keystream, text_length, LFSR_SEED);

    char encrypted[256];
    xor_encrypt_decrypt(plaintext, encrypted, keystream, text_length);

    printf("Encrypted text: ");
    for (size_t i = 0; i < text_length; i++) {
        printf("%02X ", (unsigned char)encrypted[i]);
    }
    printf("\n");

    char decrypted[256];
    xor_encrypt_decrypt(encrypted, decrypted, keystream, text_length);

    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
