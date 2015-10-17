#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>
#include <stdio.h>

#include "crypto.hpp"

using namespace std;

Crypto::Crypto() {
	RAND_bytes(aes_key, AES_KEYLEN/8);
	RAND_bytes(aes_iv, AES_KEYLEN/8);

	aes_ctx = new EVP_CIPHER_CTX();
	EVP_CIPHER_CTX_init(aes_ctx);
}

string Crypto::aes_encrypt(string dec_msg) {
	size_t block_len = 0;
	size_t enc_msg_len = 0;	
	unsigned char enc_msg[msg.size() + AES_BLOCK_SIZE];

	EVP_EncryptInit_ex(aes_ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);
	EVP_EncryptUpdate(aes_ctx, enc_msg, (int*)&block_len, (unsigned char*)dec_msg.c_str(), dec_msg.size());
	enc_msg_len += block_len;
	EVP_EncryptFinal_ex(aes_ctx, enc_msg + enc_msg_len, (int*)&block_len);
	enc_msg_len += block_len;

	EVP_CIPHER_CTX_cleanup(aes_ctx);

	string ret (reinterpret_cast<char*>(enc_msg));
	return ret;
}

string Crypto::aes_decrypt(string enc_msg) {
	size_t block_len = 0;
	size_t enc_msg_len = 0;	
	unsigned char dec_msg[enc_msg.size()];

	EVP_DecryptInit_ex(aes_ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);
	EVP_DecryptUpdate(aes_ctx, dec_msg, (int*)&block_len, (unsigned char*)enc_msg, (int)enc_msg_len);

	string ret (reinterpret_cast<char*>(dec_msg));
	return ret;
}