#include <gtest/gtest.h>

// core includes
#include <crypto/Crypto.h>
#include <crypto/ICrypto.h>
//#include<system/vhelper.hpp>
#include<system/shelper.h>

using namespace neopt;

TEST(CryptoTest, Test_Hash160_Empty)
{
   Crypto crypto;
   vbyte v(0); // '': empty byte array
   EXPECT_EQ(crypto.Hash160(v), crypto.RIPEMD160(crypto.Sha256(v)));
}

TEST(CryptoTest, Test_Hash160_Zero)
{
   Crypto crypto;
   vbyte v(1, 0); // 0x00
   EXPECT_EQ(crypto.Hash160(v), crypto.RIPEMD160(crypto.Sha256(v)));
}

TEST(CryptoTest, Test_Hash256_Empty)
{
   Crypto crypto;
   vbyte v(0); // '': empty byte array
   EXPECT_EQ(crypto.Hash256(v), crypto.Sha256(crypto.Sha256(v)));
}

TEST(CryptoTest, Test_Hash256_Zero)
{
   Crypto crypto;
   vbyte v(1, 0); // 0x00
   EXPECT_EQ(crypto.Hash256(v), crypto.Sha256(crypto.Sha256(v)));
}

// verification tests

TEST(CryptoTest, Test_SignData_EmptyMessage)
{
   Crypto crypto;
   vbyte msg(0); // '': empty message

   // creating private/public key pair (random each test)
   vbyte mypubkey;
   vbyte myprivkey = crypto.GeneratePrivateKey(mypubkey);

   // sign empty message
   vbyte sig = crypto.SignData(crypto.Sha256(msg), myprivkey, mypubkey);

   // test if signature matches public key for message
   EXPECT_EQ(crypto.VerifySignature(msg, sig, mypubkey), 1);
}

TEST(CryptoTest, Test_Keccak_Empty)
{
   Crypto crypto;
   vbyte v(0); // '': empty byte array
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("c5d2460186f7233c927e7db2dcc703c0e500b653ca82273b7bfad8045d85a470"));
}


TEST(CryptoTest, Test_Keccak_UInt160_Zero)
{
   Crypto crypto;
   vbyte v(20, 0x00);
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("5380c7b7ae81a58eb98d9c78de4a1fd7fd9535fc953ed2be602daaa41767312a"));
}

TEST(CryptoTest, Test_Keccak_Empty_List_RLP)
{
   Crypto crypto;
   vbyte v(1, 0xc0); // empty list RLP encoding
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347"));
}

TEST(CryptoTest, Test_Keccak_hello)
{
   Crypto crypto;
   vbyte v = shelper::HexToBytes(shelper::ASCIIToHexString("hello"));
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("1c8aff950685c2ed4bc3174f3472287b56d9517b9c948127319a09a7a36deac8"));
}

