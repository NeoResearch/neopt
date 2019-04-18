#ifndef LIB_CRYPTO_OPENSSL_H
#define LIB_CRYPTO_OPENSSL_H

// implementation of ICrypto for openssl

// system includes
#include <string.h>

// third-party includes
#include <openssl/obj_mac.h> // for NID_secp192k1

#include <openssl/ec.h>      // for EC_GROUP_new_by_curve_name, EC_GROUP_free, EC_KEY_new, EC_KEY_set_group, EC_KEY_generate_key, EC_KEY_free
#include <openssl/ecdsa.h>   // for ECDSA_do_sign, ECDSA_do_verify
#include <openssl/sha.h>
#include <openssl/ripemd.h>

// core includes
#include<crypto/ICrypto.h>


namespace neopt
{

// cryptography for Neo using openssl
class CryptoNeoOpenSSL : public ICrypto
{
public:
   vbyte Hash160(const vbyte& message);

   vbyte Hash256(const vbyte& message);

   bool VerifySignature(const vbyte& message, const vbyte& signature, const vbyte& pubkey);

   // SHA256
   vbyte SHA256(const vbyte& message);

   // RIPEMD160
   vbyte RIPEMD160(const vbyte& message);


public:
   // borrowed from the neo-HyperVM project

	// Constants
	static const int32 SHA1_LENGTH = 20;
	static const int32 SHA256_LENGTH = 32;
   static const int32 RIPEMD160_LENGTH = 20;
	static const int32 HASH160_LENGTH = RIPEMD160_LENGTH;
	static const int32 HASH256_LENGTH = SHA256_LENGTH;

	// Methods
	static void lComputeSHA1(byte* data, int32 length, byte* output);
	static void lComputeSHA256(const byte* data, int32 length, byte* output);
	static void lComputeHash160(const byte* data, int32 length, byte* output);
	static void lComputeHash256(const byte* data, int32 length, byte* output);

	// -1=ERROR , 0= False , 1=True
	static int16 lVerifySignature(const byte* data, int32 dataLength, const byte* signature, int32 signatureLength, const byte* pubKey, int32 pubKeyLength);

private:
	static const int32 _curve = NID_X9_62_prime256v1; // secp256r1
   // see: https://www.ietf.org/rfc/rfc5480.txt

	// Empty hashes

	static const byte EMPTY_HASH160[HASH160_LENGTH];
	static const byte EMPTY_HASH256[HASH256_LENGTH];
	static const byte EMPTY_SHA1[SHA1_LENGTH];
	static const byte EMPTY_SHA256[SHA256_LENGTH];
};

}

#endif
