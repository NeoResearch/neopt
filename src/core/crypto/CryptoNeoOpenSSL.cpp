#include <crypto/CryptoNeoOpenSSL.h>

using namespace neopt;

// ==================
// external functions
// ==================

vbyte CryptoNeoOpenSSL::Hash160(const vbyte& message)
{
	vbyte voutput(HASH160_LENGTH);
	lComputeHash160(message.data(), message.size(), voutput.data());
	return voutput;
}

vbyte CryptoNeoOpenSSL::Hash256(const vbyte& message)
{
	vbyte voutput(HASH256_LENGTH);
	lComputeHash256(message.data(), message.size(), voutput.data());
	return voutput;
}

bool CryptoNeoOpenSSL::VerifySignature(const vbyte& message, const vbyte& signature, const vbyte& pubkey)
{
	int16 ret = lVerifySignature(message.data(), message.size(), signature.data(), signature.size(), pubkey.data(), pubkey.size());
	if (ret==-1)
		NEOPT_EXCEPTION("ERROR ON VerifySignature");
	return ret == 1;
}

vbyte CryptoNeoOpenSSL::SHA256(const vbyte& message)
{
	vbyte voutput(SHA256_LENGTH);
	lComputeSHA256(message.data(), message.size(), voutput.data());
	return voutput;
}

// message is already received as a SHA256 digest
// TODO: better to receive pubkey in general format or specific ECPoint(X,Y) ?
vbyte CryptoNeoOpenSSL::SignData(const vbyte& digest, const vbyte& privkey, const vbyte& pubkey)
{
	// TODO: implement low level lSignData? (or keep C++ mixed?)
	// TODO: apply SHA256 here to make sure?
	const byte* hash   = digest.data();
	int hashLen = 32;
	assert(digest.size() == hashLen);
	const byte* pubKey = pubkey.data();
	int pubKeyLength   = pubkey.size();
	const byte* mypriv = privkey.data();

	// initialize environment and initialize private key
	EC_KEY *eckey=EC_KEY_new();
	if (NULL == eckey)
	{
	  NEOPT_EXCEPTION("Failed to create new EC Key");
	  return vbyte(0);
	}

	EC_GROUP *ecgroup= EC_GROUP_new_by_curve_name(_curve);//NID_secp192k1);
	if (NULL == ecgroup)
	{
		NEOPT_EXCEPTION("Failed to create new EC Group");
		return vbyte(0);
	}

	int set_group_status = EC_KEY_set_group(eckey, ecgroup);
	const int set_group_success = 1;
	if (set_group_success != set_group_status)
	{
		NEOPT_EXCEPTION("Failed to set group for EC Key");
		return vbyte(0);
	}


	byte* realPubKey = nullptr;
	int realPublicKeyLength = 65;

	if (pubKeyLength == 33 && (pubKey[0] == 0x02 || pubKey[0] == 0x03))
	{
		// remove const from array: must make sure realPubKey data is never changed
		realPubKey = const_cast<byte*>(pubKey);
		realPublicKeyLength = 33;
	}
	else if (pubKeyLength == 64)
	{
		// 0x04 first

		// TODO: verify if no leak happens in this case
		realPubKey = new byte[65];
		realPubKey[0] = 0x04;

		memcpy(&realPubKey[1], pubKey, 64);
	}
	else if (pubKeyLength == 65)
	{
		if (pubKey[0] != 0x04)
		{
			NEOPT_EXCEPTION("Error on signing");
			return vbyte(0);
		}

		// remove const from array: must make sure realPubKey data is never changed
		realPubKey = const_cast<byte*>(pubKey);
	}
	else if (pubKeyLength != 65)
	{
		NEOPT_EXCEPTION("Error on signing 2");
		return vbyte(0);
	}

	BIGNUM* bn    = BN_bin2bn(realPubKey, realPublicKeyLength, nullptr);
	EC_POINT* pub = EC_POINT_bn2point(ecgroup, bn, nullptr, nullptr);
	BIGNUM*  priv = BN_bin2bn(&mypriv[0], 32, nullptr);

	if (pub != nullptr)
	{
		int32 gen_status = EC_KEY_set_public_key(eckey, pub);
		int32 gen_status2 = EC_KEY_set_private_key(eckey, priv);
	}

	// TODO: follow example: https://stackoverflow.com/questions/2228860/signing-a-message-using-ecdsa-in-openssl

	ECDSA_SIG *signature = ECDSA_do_sign(hash, hashLen, eckey);
	if (NULL == signature)
	{
		 NEOPT_EXCEPTION("Failed to generate EC Signature\n");
		 return vbyte(0);
	}

	//BIGNUM* r = BN_new();
	//BIGNUM* s = BN_new();
	//ECDSA_SIG_get0(signature, &r, &s); // TODO: DER ??

	// DER
	int der_len = ECDSA_size(eckey);
	byte* der = (byte*)calloc(der_len, sizeof(byte));
	i2d_ECDSA_SIG(signature, &der);
	//int conv_error = BN_bn2bin(priv, vpriv.data());

	vbyte vsig(der, der+der_len);

	ECDSA_SIG_free(signature);


	return std::move(vsig);
}

// =========================
// internal implementations
// =========================


const byte CryptoNeoOpenSSL::EMPTY_SHA1[] =
{
	0xda,0x39,0xa3,0xee,0x5e,0x6b,0x4b,0x0d,0x32,0x55,
	0xbf,0xef,0x95,0x60,0x18,0x90,0xaf,0xd8,0x07,0x09
};

const byte CryptoNeoOpenSSL::EMPTY_HASH160[] =
{
	0xb4,0x72,0xa2,0x66,0xd0,0xbd,0x89,0xc1,0x37,0x06,
	0xa4,0x13,0x2c,0xcf,0xb1,0x6f,0x7c,0x3b,0x9f,0xcb
};

const byte CryptoNeoOpenSSL::EMPTY_SHA256[] =
{
	0xe3,0xb0,0xc4,0x42,0x98,0xfc,0x1c,0x14,0x9a,0xfb,0xf4,0xc8,0x99,0x6f,0xb9,0x24,
	0x27,0xae,0x41,0xe4,0x64,0x9b,0x93,0x4c,0xa4,0x95,0x99,0x1b,0x78,0x52,0xb8,0x55
};

const byte CryptoNeoOpenSSL::EMPTY_HASH256[] =
{
	0x5d,0xf6,0xe0,0xe2,0x76,0x13,0x59,0xd3,0x0a,0x82,0x75,0x05,0x8e,0x29,0x9f,0xcc,
	0x03,0x81,0x53,0x45,0x45,0xf5,0x5c,0xf4,0x3e,0x41,0x98,0x3f,0x5d,0x4c,0x94,0x56
};


int16 CryptoNeoOpenSSL::lVerifySignature
(
	const byte* data, int32 dataLength,
	const byte* signature, int32 signatureLength,
	const byte* pubKey, int32 pubKeyLength
)
{
	if (signatureLength != 64)
		return -1;

	byte* realPubKey = nullptr;
	int32 realPublicKeyLength = 65;

	if (pubKeyLength == 33 && (pubKey[0] == 0x02 || pubKey[0] == 0x03))
	{
		// remove const from array: must make sure realPubKey data is never changed
		realPubKey = const_cast<byte*>(pubKey);
		realPublicKeyLength = 33;
	}
	else if (pubKeyLength == 64)
	{
		// 0x04 first

		// TODO: verify if no leak happens in this case
		realPubKey = new byte[65];
		realPubKey[0] = 0x04;

		memcpy(&realPubKey[1], pubKey, 64);
	}
	else if (pubKeyLength == 65)
	{
		if (pubKey[0] != 0x04)
			return -1;

		// remove const from array: must make sure realPubKey data is never changed
		realPubKey = const_cast<byte*>(data);
	}
	else if (pubKeyLength != 65)
	{
		return -1;
	}

	int32 ret = -1;
	EC_GROUP* ecgroup = EC_GROUP_new_by_curve_name(_curve);

	if (ecgroup != nullptr)
	{
		EC_KEY* eckey = EC_KEY_new_by_curve_name(_curve);

		if (eckey != nullptr)
		{
			BIGNUM* bn = BN_bin2bn(realPubKey, realPublicKeyLength, nullptr);
			EC_POINT* pub = EC_POINT_bn2point(ecgroup, bn, nullptr, nullptr);

			if (pub != nullptr)
			{
				int32 gen_status = EC_KEY_set_public_key(eckey, pub);

				if (gen_status == 0x01)
				{
					// DER encoding

					BIGNUM* r = BN_bin2bn(&signature[0], 32, nullptr);
					BIGNUM* s = BN_bin2bn(&signature[32], 32, nullptr);

					ECDSA_SIG* sig = ECDSA_SIG_new();
					gen_status = ECDSA_SIG_set0(sig, r, s);

					if (sig != nullptr)
					{
						if (gen_status == 0x01)
						{
							byte hash[CryptoNeoOpenSSL::SHA256_LENGTH];
							lComputeSHA256(data, dataLength, hash);
							ret = ECDSA_do_verify(hash, CryptoNeoOpenSSL::SHA256_LENGTH, sig, eckey);
						}

						// Free r,s and sig

						ECDSA_SIG_free(sig);
					}
					else
					{
						// TODO: Check this free

						BN_free(r);
						BN_free(s);
					}
				}

				EC_POINT_free(pub);
				BN_free(bn);
			}
			EC_KEY_free(eckey);
		}
		EC_GROUP_free(ecgroup);
	}

	// free

	if (realPubKey != pubKey)
	{
		delete[](realPubKey);
	}

	return ret == 0x01 ? 0x01 : 0x00;
}

// generates private key and updates parameter vpubkey (TODO: update function format)
vbyte CryptoNeoOpenSSL::GeneratePrivateKey(vbyte& vpubkey)
{
	printf("generating priv/pub key\n");
	EC_KEY *eckey=EC_KEY_new();
	if (NULL == eckey)
	{
	  NEOPT_EXCEPTION("Failed to create new EC Key");
	  return vbyte(0);
	}

	EC_GROUP *ecgroup= EC_GROUP_new_by_curve_name(_curve); //NID_secp192k1);
	if (NULL == ecgroup)
	{
	   NEOPT_EXCEPTION("Failed to create new EC Group");
	   return vbyte(0);
	}

	int set_group_status = EC_KEY_set_group(eckey, ecgroup);
	const int set_group_success = 1;
	if (set_group_success != set_group_status)
	{
		NEOPT_EXCEPTION("Failed to set group for EC Key");
		return vbyte(0);
	}

	const int gen_success = 1;
	int gen_status = EC_KEY_generate_key(eckey);
	if (gen_success != gen_status)
	{
		NEOPT_EXCEPTION("Failed to generate EC Key");
		return vbyte(0);
	}

	//EC_POINT* pub = EC_KEY_get0_public_key(eckey);
	const BIGNUM* priv = EC_KEY_get0_private_key(eckey);
	vbyte vpriv(32);
	int conv_error = BN_bn2bin(priv, vpriv.data());

	char * number_str = BN_bn2hex(priv);
	printf("private_key hexstr: %s\n", number_str);
	free(number_str);

	BN_CTX *ctx;
   ctx = BN_CTX_new(); // ctx is an optional buffer to save time from allocating and deallocating memory whenever required

	// plan A
	const EC_POINT *pub_key = EC_KEY_get0_public_key(eckey);
	// plan B
   //EC_POINT* pub_key = EC_POINT_new(ecgroup);
   //if (!EC_POINT_mul(ecgroup, pub_key, priv, NULL, NULL, ctx))
	//{
	//	NEOPT_EXCEPTION("Error at EC_POINT_mul. Getting pubkey failed.");
	//	return vbyte(0);
	//}


	printf("printing pubkey:\n");
	/*
   // print plan A
	BIGNUM *x = BN_new();
	BIGNUM *y = BN_new();
	if (EC_POINT_get_affine_coordinates_GFp(ecgroup, pub_key, x, y, NULL)) {
		 BN_print_fp(stdout, x);
		 putc('\n', stdout);
		 BN_print_fp(stdout, y);
		 putc('\n', stdout);
	}

	// print plan B
	char *cc = EC_POINT_point2hex(ecgroup, pub_key, POINT_CONVERSION_UNCOMPRESSED, ctx);
	printf("pubkey (uncompressed): %d %s\n", strlen(cc), cc);
	std::string scc(cc);
	printf("mystr: %s\n", scc.c_str());
	vpubkey = CryptoNeoOpenSSL::FromHexString(scc);
	//free(cc);
	*/

	/*
	char *cc2 = EC_POINT_point2hex(ecgroup, pub_key, POINT_CONVERSION_COMPRESSED, ctx);
	printf("pubkey (compressed): %s\n", cc2);
	free(cc2);
	*/

   // point_conversion_form_t
	vpubkey = vbyte(33);
	//byte* pubkdata = vpubkey.data();
	size_t converr = EC_POINT_point2oct(ecgroup, pub_key, POINT_CONVERSION_COMPRESSED, vpubkey.data(), vpubkey.size(), ctx);


//     assert(EC_POINT_bn2point(group, &res, pub_key, ctx)); // Null here

	////EC_KEY_set_public_key(eckey, pub_key);


	BN_CTX_free(ctx);
	EC_KEY_free(eckey);
	//EC_POINT_free(pub_key);
	EC_GROUP_free(ecgroup);

	return std::move(vpriv);
}

void CryptoNeoOpenSSL::lComputeHash160(const byte* data, int32 length, byte* output)
{
	if (length <= 0)
	{
		memcpy(output, CryptoNeoOpenSSL::EMPTY_HASH160, CryptoNeoOpenSSL::HASH160_LENGTH);
		return;
	}

	byte digest[SHA256_DIGEST_LENGTH];

	// First SHA256

	lComputeSHA256(data, length, digest);

	// Then RIPEMD160

	RIPEMD160_CTX c;

	RIPEMD160_Init(&c);
	RIPEMD160_Update(&c, digest, SHA256_DIGEST_LENGTH);
	RIPEMD160_Final(output, &c);
	OPENSSL_cleanse(&c, sizeof(c));
}

void CryptoNeoOpenSSL::lComputeHash256(const byte* data, int32 length, byte* output)
{
	if (length <= 0)
	{
		memcpy(output, CryptoNeoOpenSSL::EMPTY_HASH256, CryptoNeoOpenSSL::HASH256_LENGTH);
		return;
	}

	byte digest[SHA256_LENGTH];

	// First SHA256

	lComputeSHA256(data, length, digest);

	// Then SHA256 Again

	lComputeSHA256(digest, SHA256_LENGTH, output);
}

void CryptoNeoOpenSSL::lComputeSHA256(const byte* data, int32 length, byte* output)
{
	if (length <= 0)
	{
		memcpy(output, CryptoNeoOpenSSL::EMPTY_SHA256, CryptoNeoOpenSSL::SHA256_LENGTH);
		return;
	}

	SHA256_CTX c;
	SHA256_Init(&c);
	SHA256_Update(&c, data, length);
	SHA256_Final(output, &c);
	OPENSSL_cleanse(&c, sizeof(c));
}

void CryptoNeoOpenSSL::lComputeSHA1(byte* data, int32 length, byte* output)
{
	if (length <= 0)
	{
		memcpy(output, CryptoNeoOpenSSL::EMPTY_SHA1, CryptoNeoOpenSSL::SHA1_LENGTH);
		return;
	}

	SHA_CTX c;
	SHA1_Init(&c);
	SHA1_Update(&c, data, length);
	SHA1_Final(output, &c);
	OPENSSL_cleanse(&c, sizeof(c));
}
