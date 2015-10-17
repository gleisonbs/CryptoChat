#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

#include "crypto.hpp"

using namespace std;

Crypto::Crypto() {
	RAND_bytes(aes_key, AES_KEYLEN/8);
	RAND_bytes(aes_iv, AES_KEYLEN/8);

	aes_ctx = new EVP_CIPHER_CTX();
	EVP_CIPHER_CTX_init(aes_ctx);
}

Crypto::~Crypto() {
	//free(aes_key);
	//free(aes_iv);
	free(aes_ctx);
}

string Crypto::aes_encrypt(string dec_msg) {
	size_t block_len = 0;
	size_t enc_msg_len = 0;	
	unsigned char enc_msg[dec_msg.size() + AES_BLOCK_SIZE];

	EVP_EncryptInit_ex(aes_ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);
	EVP_EncryptUpdate(aes_ctx, enc_msg, (int*)&block_len, (unsigned char*)dec_msg.c_str(), dec_msg.size());
	enc_msg_len += block_len;
	EVP_EncryptFinal_ex(aes_ctx, enc_msg + enc_msg_len, (int*)&block_len);
	enc_msg_len += block_len;

	EVP_CIPHER_CTX_cleanup(aes_ctx);
	cout << enc_msg << endl;

	string ret;
	for(size_t i = 0; i < enc_msg_len; ++i) {
		char hex_char[3];
		cout << enc_msg[i] << " - ";
		sprintf(hex_char, "%02x", enc_msg[i]);
		cout << hex_char << endl;
		ret += hex_char;
	}
	return ret;
}

string Crypto::aes_decrypt(string enc_msg_hex) {
	size_t block_len = 0;
	size_t dec_msg_len = 0;	
	unsigned char dec_msg[enc_msg_hex.size()];

	unsigned char dec_char;
	stringstream ss;
	string enc_msg = "";
	for(size_t i = 0; i < enc_msg_hex.size(); i+=2) {
		string s = "";
		s += enc_msg_hex[i];
		s += enc_msg_hex[i+1];
		cout << s << " - ";
		dec_char = stoul(s, nullptr, 16);
		cout << dec_char << endl;
		enc_msg += dec_char;
	}
	cout << enc_msg << endl;
	
	EVP_DecryptInit_ex(aes_ctx, EVP_aes_256_cbc(), NULL, aes_key, aes_iv);
	EVP_DecryptUpdate(aes_ctx, dec_msg, (int*)&block_len, (unsigned char*)enc_msg.c_str(), (int)dec_msg_len);
	dec_msg_len += block_len;
	EVP_DecryptFinal(aes_ctx, dec_msg + dec_msg_len, (int*)&block_len);

	EVP_CIPHER_CTX_cleanup(aes_ctx);

	string ret (reinterpret_cast<char*>(dec_msg));
	return ret;
}