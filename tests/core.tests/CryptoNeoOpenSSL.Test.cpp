#include<gtest/gtest.h>

// core includes
#include<crypto/ICrypto.h>
#include<crypto/CryptoNeoOpenSSL.h>
#include<system/vhelper.h>

using namespace neopt;

TEST(CryptoTest, Test_Hash160_Empty)
{
	CryptoNeoOpenSSL crypto;
   vbyte v(0); // '': empty byte array
	EXPECT_EQ(crypto.Hash160(v), crypto.RIPEMD160(crypto.Sha256(v)));
}

TEST(CryptoTest, Test_Hash160_Zero)
{
	CryptoNeoOpenSSL crypto;
   vbyte v(1, 0); // 0x00
	EXPECT_EQ(crypto.Hash160(v), crypto.RIPEMD160(crypto.Sha256(v)));
}

TEST(CryptoTest, Test_Hash256_Empty)
{
	CryptoNeoOpenSSL crypto;
   vbyte v(0); // '': empty byte array
	EXPECT_EQ(crypto.Hash256(v), crypto.Sha256(crypto.Sha256(v)));
}

TEST(CryptoTest, Test_Hash256_Zero)
{
	CryptoNeoOpenSSL crypto;
   vbyte v(1, 0); // 0x00
	EXPECT_EQ(crypto.Hash256(v), crypto.Sha256(crypto.Sha256(v)));
}
