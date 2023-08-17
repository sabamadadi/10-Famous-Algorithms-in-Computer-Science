#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>

// Function to generate an RSA key pair
RSA* generateRSAKey() {
    RSA* rsaKey = nullptr;
    BIGNUM* bne = nullptr;
    BIO* bpPrivate = nullptr;
    BIO* bpPublic = nullptr;

    int bits = 2048;
    unsigned long e = RSA_F4;

    // Initialize the BIGNUM structure
    bne = BN_new();
    BN_set_word(bne, e);

    // Generate the RSA key pair
    rsaKey = RSA_new();
    RSA_generate_key_ex(rsaKey, bits, bne, nullptr);

    // Write the RSA private key to a BIO
    bpPrivate = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bpPrivate, rsaKey, nullptr, nullptr, 0);

    // Write the RSA public key to a BIO
    bpPublic = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bpPublic, rsaKey);

    // Cleanup and return the RSA key pair
    RSA_free(rsaKey);
    BN_free(bne);
    BIO_free_all(bpPrivate);
    BIO_free_all(bpPublic);

    return rsaKey;
}

// Function to encrypt a message using RSA public key
std::string encryptRSA(const std::string& message, RSA* rsaKey) {
    std::string encryptedMessage;

    int rsaSize = RSA_size(rsaKey);
    char* encryptedBuffer = new char[rsaSize];

    int encryptedLength = RSA_public_encrypt(
        static_cast<int>(message.size()),    // Input data length
        reinterpret_cast<const unsigned char*>(message.c_str()),  // Input data
        reinterpret_cast<unsigned char*>(encryptedBuffer),       // Encrypted data
        rsaKey, RSA_PKCS1_PADDING);   // RSA key and padding scheme

    if (encryptedLength != -1) {
        encryptedMessage.assign(encryptedBuffer, encryptedLength);
    }

    delete[] encryptedBuffer;

    return encryptedMessage;
}

// Function to decrypt a message using RSA private key
std::string decryptRSA(const std::string& encryptedMessage, RSA* rsaKey) {
    std::string decryptedMessage;

    int rsaSize = RSA_size(rsaKey);
    char* decryptedBuffer = new char[rsaSize];

    int decryptedLength = RSA_private_decrypt(
        static_cast<int>(encryptedMessage.size()),  // Encrypted data length
        reinterpret_cast<const unsigned char*>(encryptedMessage.c_str()),  // Encrypted data
        reinterpret_cast<unsigned char*>(decryptedBuffer),  // Decrypted data
        rsaKey, RSA_PKCS1_PADDING);   // RSA key and padding scheme

    if (decryptedLength != -1) {
        decryptedMessage.assign(decryptedBuffer, decryptedLength);
    }

    delete[] decryptedBuffer;

    return decryptedMessage;
}

int main() {
    // Generate RSA key pair
    RSA* rsaKey = generateRSAKey();

    // Message to be encrypted
    std::string message = "Hello, RSA encryption!";

    // Encrypt the message using RSA public key
    std::string encryptedMessage = encryptRSA(message, rsaKey);
    std::cout << "Encrypted message: " << encryptedMessage << std::endl;

    // Decrypt the message using RSA private key
    std::string decryptedMessage = decryptRSA(encryptedMessage, rsaKey);
    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    // Cleanup
    RSA_free(rsaKey);

    return 0;
}
