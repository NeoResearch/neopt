#include <gtest/gtest.h>

// core includes
#include <adt/MerklePatriciaTrie.hpp>

using namespace std;
using namespace neopt;

TEST(MerklePatriciaTrieTests, Test_MPT_CompactEncode)
{
   // even-size: not terminator on end (0x10)
   vnibble path0  = {0x0, 0X1, 0X2, 0X3, 0X4, 0X5};
   EXPECT_EQ(MPTNode::CompactEncode(path0), vbyte({0x00, 0x01, 0x23, 0x45}));

   // odd-size: not terminator on end (0x10)
   vnibble path1  = {0X1, 0X2, 0X3, 0X4, 0X5};
   EXPECT_EQ(MPTNode::CompactEncode(path1), vbyte({0x11, 0x23, 0x45}));

   // even-size: terminator on end (0x10)
   vnibble path2  = {0x0, 0xf, 0X1, 0Xc, 0Xb, 0X8, 0x10};
   EXPECT_EQ(MPTNode::CompactEncode(path2), vbyte({0x20, 0x0f, 0x1c, 0xb8}));

   // odd-size: terminator on end (0x10)
   vnibble path3  = {0xf, 0X1, 0Xc, 0Xb, 0X8, 0x10};
   EXPECT_EQ(MPTNode::CompactEncode(path3), vbyte({0x3f, 0x1c, 0xb8}));
}

// rlp.encode(['hellothere']) => cb 8a 68 65 6c 6c 6f 74 68 65 72 65
// state.update('\x01\x01\x02', rlp.encode(['hellothere']))

   // = [](const UInt256& p) -> MerkleTreeNode* { return new MerkleTreeNode(p); };
   // Crypto::Default().Hash256(this->ToArray());

TEST(MerklePatriciaTrieTests, Test_MPT_SimpleHashNull_Hash256)
{
   std::function<vbyte(const vbyte&)> fhash = [](const vbyte& p) -> vbyte { return Crypto::Default().Hash256(p); };
   
   MPTNode node(fhash);
   std::cout << node.hash << std::endl;
   EXPECT_EQ(node.hash, shelper::HexToBytes("5df6e0e2761359d30a8275058e299fcc0381534545f55cf43e41983f5d4c9456")); // TODO: verify!
   // TODO: THIS HASH WAS NOT TESTED YET!! Do this after some Keccak testing
   //EXPECT_EQ(1,2);
}


TEST(MerklePatriciaTrieTests, Test_Keccak_Empty)
{
   Crypto crypto;
   vbyte v(0); // '': empty byte array
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("c5d2460186f7233c927e7db2dcc703c0e500b653ca82273b7bfad8045d85a470"));
}


TEST(MerklePatriciaTrieTests, Test_Keccak_UInt160_Zero)
{
   Crypto crypto;
   vbyte v(20, 0x00);
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("5380c7b7ae81a58eb98d9c78de4a1fd7fd9535fc953ed2be602daaa41767312a"));
}

TEST(MerklePatriciaTrieTests, Test_Keccak_Empty_List_RLP)
{
   Crypto crypto;
   vbyte v(1, 0xc0); // empty list RLP encoding
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347"));
}

TEST(MerklePatriciaTrieTests, Test_Keccak_hello)
{
   Crypto crypto;
   vbyte v = shelper::HexToBytes(shelper::ASCIIToHexString("hello"));
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("1c8aff950685c2ed4bc3174f3472287b56d9517b9c948127319a09a7a36deac8"));
}


TEST(MerklePatriciaTrieTests, Test_MPT_CompactEncode_Leaf_0x010203)
{
   vbyte content = {0x01, 0x02, 0x03};
   vnibble path = vhelper::BytesToNibbles(content);
   path.push_back(0x10); // terminator for leaves
   EXPECT_EQ(MPTNode::CompactEncode(path), vbyte({0x20, 0x01, 0x02, 0x03}));
}
