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
   EXPECT_EQ(node.hash, shelper::HexToBytes("5df6e0e2761359d30a8275058e299fcc0381534545f55cf43e41983f5d4c9456"));
   // TODO: THIS HASH WAS NOT TESTED YET!! Do this after some Keccak testing
}