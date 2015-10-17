#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <openssl/evp.h>
#include <string>

constexpr int AES_KEYLEN = 256;

class Crypto {
public:
	Crypto();
	~Crypto();
	std::string aes_encrypt(std::string);
	std::string aes_decrypt(std::string);
private:
	unsigned char aes_key[AES_KEYLEN/8];
	unsigned char aes_iv[AES_KEYLEN/8];

	EVP_CIPHER_CTX *aes_ctx;
};

#endif // CRYPTO_HPP