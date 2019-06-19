#include <gtest/gtest.h>

// core includes
#include <adt/MerklePatriciaTrie.hpp>
#include <crypto/CryptoExtra.h>
#include <system/BinaryReader.hpp>
#include <system/BinaryWriter.hpp>

using namespace std;
using namespace neopt;

TEST(MerklePatriciaTrieTests, Test_MPT_CompactEncode)
{
   // even-size: not terminator
   vnibble path0 = { 0x0, 0X1, 0X2, 0X3, 0X4, 0X5 };
   EXPECT_EQ(MPTNode::CompactEncode(path0), vbyte({ 0x00, 0x01, 0x23, 0x45 }));

   // odd-size: not terminator
   vnibble path1 = { 0X1, 0X2, 0X3, 0X4, 0X5 };
   EXPECT_EQ(MPTNode::CompactEncode(path1), vbyte({ 0x11, 0x23, 0x45 }));

   // even-size: terminator
   vnibble path2 = { 0x0, 0xf, 0X1, 0Xc, 0Xb, 0X8 };
   EXPECT_EQ(MPTNode::CompactEncode(path2, true), vbyte({ 0x20, 0x0f, 0x1c, 0xb8 }));

   // odd-size: terminator
   vnibble path3 = { 0xf, 0X1, 0Xc, 0Xb, 0X8 };
   EXPECT_EQ(MPTNode::CompactEncode(path3, true), vbyte({ 0x3f, 0x1c, 0xb8 }));
}

TEST(MerklePatriciaTrieTests, Test_MPT_CompactDecodeEncode)
{
   bool isLeaf; // used as in/out parameter

   // even-size: not terminator
   vbyte vpath0 = vbyte({ 0x00, 0x01, 0x23, 0x45 }); // 0 1 2 3 4 5
   vnibble nibbles0 = MPTNode::CompactDecode(vpath0, isLeaf);
   EXPECT_EQ(vpath0, MPTNode::CompactEncode(nibbles0, isLeaf));

   // odd-size: not terminator
   vbyte vpath1 = vbyte({ 0x11, 0x23, 0x45 }); // 1 2 3 4 5
   vnibble nibbles1 = MPTNode::CompactDecode(vpath1, isLeaf);
   EXPECT_EQ(vpath1, MPTNode::CompactEncode(nibbles1, isLeaf));

   // even-size: terminator
   vbyte vpath2 = vbyte({ 0x20, 0x0f, 0x1c, 0xb8 }); // 0 f 1 c b 8
   vnibble nibbles2 = MPTNode::CompactDecode(vpath2, isLeaf);
   EXPECT_EQ(vpath2, MPTNode::CompactEncode(nibbles2, isLeaf));

   // odd-size: terminator
   vbyte vpath3 = vbyte({ 0x3f, 0x1c, 0xb8 }); // f 1 c b 8
   vnibble nibbles3 = MPTNode::CompactDecode(vpath3, isLeaf);
   EXPECT_EQ(vpath3, MPTNode::CompactEncode(nibbles3, isLeaf));
}

TEST(MerklePatriciaTrieTests, Test_MPT_SimpleHashNull_Hash256)
{
   std::function<vbyte(const vbyte&)> fhash = [](const vbyte& p) -> vbyte { return Crypto::Default().Hash256(p); };

   MPTNode node(fhash);

   // null node is an empty array... but array serialization is 0x00
   EXPECT_EQ(node.ToArray(), vbyte(1, 0x00));

   //std::cout << vhelper::ToHexString(node.hash) << std::endl;
   EXPECT_EQ(node.hash, shelper::HexToBytes("1406e05881e299367766d313e26c05564ec91bf721d31726bd6e46e60689539a"));

   
   Crypto crypto;
   EXPECT_EQ(crypto.Hash256(node.ToArray()), shelper::HexToBytes("1406e05881e299367766d313e26c05564ec91bf721d31726bd6e46e60689539a"));
}

TEST(MerklePatriciaTrieTests, Test_Keccak_Empty)
{
   CryptoExtra crypto;
   vbyte v(0); // '': empty byte array
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("c5d2460186f7233c927e7db2dcc703c0e500b653ca82273b7bfad8045d85a470"));
}

TEST(MerklePatriciaTrieTests, Test_Keccak_UInt160_Zero)
{
   CryptoExtra crypto;
   vbyte v(20, 0x00);
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("5380c7b7ae81a58eb98d9c78de4a1fd7fd9535fc953ed2be602daaa41767312a"));
}

TEST(MerklePatriciaTrieTests, Test_Keccak_Empty_List_RLP)
{
   CryptoExtra crypto;
   vbyte v(1, 0xc0); // empty list RLP encoding
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347"));
}

TEST(MerklePatriciaTrieTests, Test_Keccak_hello)
{
   CryptoExtra crypto;
   vbyte v = shelper::HexToBytes(shelper::ASCIIToHexString("hello"));
   EXPECT_EQ(v, shelper::HexToBytes("68656c6c6f"));
   EXPECT_EQ(crypto.Sha3Keccak(v), shelper::HexToBytes("1c8aff950685c2ed4bc3174f3472287b56d9517b9c948127319a09a7a36deac8"));
}


TEST(MerklePatriciaTrieTests, Test_MPT_CompactEncode_Leaf_0x010203)
{
   vbyte content = { 0x01, 0x02, 0x03 };
   vnibble path = vhelper::BytesToNibbles(content);
   EXPECT_EQ(MPTNode::CompactEncode(path, true), vbyte({ 0x20, 0x01, 0x02, 0x03 }));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Keccak_RLP_Leaf_0x010203_array_hello)
{
   // Leaf Node: [ '0x20010102', '0xc68568656c6c6f' ]
   // path is encoded
   // key represents an encoded array ['hello'] using RLP
   // RLP: cd842001010287c68568656c6c6f => 4a5b19d151e796482b08a1e020f1f7ef5ea7240c0171fd629598fee612892a7b (sha3 NIST?)
   //              or :                    15da97c42b7ed2e1c0c8dab6a6d7e3d9dc0a75580bbc4f1f29c33996d1415dcc (sha3 keccak?)
   // cd (array with 13 size)
   // 84 (4 bytes)
   // encodedPath -> "0x20010102"
   // 87 (7 bytes)
   // key -> c68568656c6c6f -> "['hello']" (in RLP)
   //                             hello -> 68656c6c6f

   vbyte content = { 0x01, 0x01, 0x02 };
   vnibble path = vhelper::BytesToNibbles(content);
   EXPECT_EQ(MPTNode::CompactEncode(path, true), vbyte({ 0x20, 0x01, 0x01, 0x02 }));

   CryptoExtra crypto;
   vbyte rlp(shelper::HexToBytes("cd842001010287c68568656c6c6f"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp), shelper::HexToBytes("15da97c42b7ed2e1c0c8dab6a6d7e3d9dc0a75580bbc4f1f29c33996d1415dcc"));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Keccak_RLP_Leaf_0x010203_array_hellothere)
{
   // Leaf Node: [ '0x20010102', '0xcb8a68656c6c6f7468657265' ]
   // path is encoded
   // key represents an encoded array ['hellothere'] using RLP
   // RLP: d284200101028ccb8a68656c6c6f7468657265 => 05e13d8be09601998499c89846ec5f3101a1ca09373a5f0b74021261af85d396 (sha3 keccak?)
   // encodedPath -> "0x20010102"
   // key -> cb8a68656c6c6f7468657265 -> "['hellothere']" (in RLP)

   CryptoExtra crypto;
   vbyte rlp(shelper::HexToBytes("d284200101028ccb8a68656c6c6f7468657265"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp), shelper::HexToBytes("05e13d8be09601998499c89846ec5f3101a1ca09373a5f0b74021261af85d396"));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Keccak_RLP_Extension_0x101010_hash)
{
   // Extension Node: [ '0x101010', '0x2201ab8375156f27f7542d68de944b2fbaa35b836c94e7b38acf0a0a74bbefd9' ]
   // path is encoded (1 means extension and odd) -> real path is 0X01010 (5 nibbles)
   // key represents a hash (keccak hash in this example)
   // serialization RLP for this node is: e583101010a02201ab8375156f27f7542d68de944b2fbaa35b836c94e7b38acf0a0a74bbefd9
   // hash of this node is: b5e187f15f1a250e51a78561e29ccfc0a7f48e06d19ce02f98dd61159e81f71d

   CryptoExtra crypto;
   vbyte rlp(shelper::HexToBytes("e583101010a02201ab8375156f27f7542d68de944b2fbaa35b836c94e7b38acf0a0a74bbefd9"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp), shelper::HexToBytes("b5e187f15f1a250e51a78561e29ccfc0a7f48e06d19ce02f98dd61159e81f71d"));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Keccak_RLP_Branch_2_3)
{
   // Branch Node (on positions 2,3): [ 0:'', 1:'', 2:[0x20, 'hello'], 3:[0x20, 'hellothere'], 4:'', ..., 15:'', 16:'' ] (17 positions)
   // Node 2 is an extension node: c92087c68568656c6c6f
   // Node 3 is an extension node: ce208ccb8a68656c6c6f7468657265
   // serialization RLP for this node is: e88080c92087c68568656c6c6fce208ccb8a68656c6c6f746865726580808080808080808080808080
   // hash of this node is: 2201ab8375156f27f7542d68de944b2fbaa35b836c94e7b38acf0a0a74bbefd9

   CryptoExtra crypto;
   vbyte rlp(shelper::HexToBytes("e88080c92087c68568656c6c6fce208ccb8a68656c6c6f746865726580808080808080808080808080"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp), shelper::HexToBytes("2201ab8375156f27f7542d68de944b2fbaa35b836c94e7b38acf0a0a74bbefd9"));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Keccak_RLP_Branch_0_17)
{
   // hello key is 010102 / hellothere key is 0101
   // Branch Node (on positions 0,17): [ 0:[0x32, ['hello']], 1:'', 2:'', ..., 15:'', 16:['hellothere'] ] (17 positions)
   // Node 0 is a leaf-odd node [0x32, "['hello']"]: c93287c68568656c6c6f
   // Node 16 is a key serialized RLP for "['hellothere']": cb8a68656c6c6f7468657265
   // serialization RLP for this node is: e6c93287c68568656c6c6f8080808080808080808080808080808ccb8a68656c6c6f7468657265
   // hash of this node is: 53a8d7b5a9d7054a5ac4c68f463408bba692537a03b18f53cdfa0fc15043e9b6

   CryptoExtra crypto;
   vbyte rlp(shelper::HexToBytes("e6c93287c68568656c6c6f8080808080808080808080808080808ccb8a68656c6c6f7468657265"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp), shelper::HexToBytes("53a8d7b5a9d7054a5ac4c68f463408bba692537a03b18f53cdfa0fc15043e9b6"));

   // a root extension-even node consumes 0101 and moves to this node
   // root: [0x000101, 0x53a8d7b5a9d7054a5ac4c68f463408bba692537a03b18f53cdfa0fc15043e9b6]
   // serialization of this node: e583000101a053a8d7b5a9d7054a5ac4c68f463408bba692537a03b18f53cdfa0fc15043e9b6
   // hash of this node: f3e46945b73ef862d59850a8e1a73ef736625dd9a02bed1c9f2cc3ff4cd798b3

   vbyte rlp2(shelper::HexToBytes("e583000101a053a8d7b5a9d7054a5ac4c68f463408bba692537a03b18f53cdfa0fc15043e9b6"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp2), shelper::HexToBytes("f3e46945b73ef862d59850a8e1a73ef736625dd9a02bed1c9f2cc3ff4cd798b3"));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Keccak_RLP_Branch_5_17)
{
   // hello key is 010102 / hellothere key is 01010257
   // Branch Node (on positions 0,17): [ 0:'', 1:'', 2:'', 3:'', 4:'', 5:[0x37, "['hellothere']"] ..., 15:'', 16:"['hello']" ] (17 positions)
   // Node 7 is a leaf-odd node [0x37, "['hellothere']"]: ce378ccb8a68656c6c6f7468657265
   // Node 16 is a key serialized RLP for "['hello']": c68568656c6c6f
   // serialization RLP for this node is: e68080808080ce378ccb8a68656c6c6f74686572658080808080808080808087c68568656c6c6f
   // hash of this node is: 59b8815f083017b6d2d53804bd17b72e1b8b122a57ead88253ce301d6dc602f8

   CryptoExtra crypto;
   vbyte rlp(shelper::HexToBytes("e68080808080ce378ccb8a68656c6c6f74686572658080808080808080808087c68568656c6c6f"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp), shelper::HexToBytes("59b8815f083017b6d2d53804bd17b72e1b8b122a57ead88253ce301d6dc602f8"));

   // a root extension-even node consumes 0101 and moves to this node
   // root: [0x00010102, 0x59b8815f083017b6d2d53804bd17b72e1b8b122a57ead88253ce301d6dc602f8]
   // serialization of this node: e68400010102a059b8815f083017b6d2d53804bd17b72e1b8b122a57ead88253ce301d6dc602f8
   // hash of this node: dfd000b4b04811e7e59f1648f887bd56c16e4c047d6267793cf0eacf4b035c34

   vbyte rlp2(shelper::HexToBytes("e68400010102a059b8815f083017b6d2d53804bd17b72e1b8b122a57ead88253ce301d6dc602f8"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp2), shelper::HexToBytes("dfd000b4b04811e7e59f1648f887bd56c16e4c047d6267793cf0eacf4b035c34"));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Keccak_RLP_Branch_jimbo)
{
   // hello key is 010102 / hellothere key is 01010255 / jimbojones key is 01010257
   // Branch Node (on positions 0,17): [ 0:'', 1:'', 2:'', 3:'', 4:'', 5:some_hash ..., 15:'', 16:"['hello']" ] (17 positions)
   // Node 5 is "some_hash", as defined above: 0x002615b7c405f6f346329a284e8fb248e735cffa89432daba29e56e414df6c30
   // Node 16 is a key serialized RLP for "['hello']": c68568656c6c6f
   // serialization RLP for this node is: f8388080808080a0002615b7c405f6f346329a284e8fb248e735cffa89432daba29e56e414df6c308080808080808080808087c68568656c6c6f
   // hash of this node is: d52faf1fde4f21753e2633685f2bac3ff1f32ab72933ece9d59f32ca6f63956d

   CryptoExtra crypto;
   vbyte rlp(shelper::HexToBytes("f8388080808080a0002615b7c405f6f346329a284e8fb248e735cffa89432daba29e56e414df6c308080808080808080808087c68568656c6c6f"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp), shelper::HexToBytes("d52faf1fde4f21753e2633685f2bac3ff1f32ab72933ece9d59f32ca6f63956d"));

   // if you follow path 0101025* you get
   // Branch Node (on positions 5,7): [ 0:'', ... , 4:'', 5:[0x20, "['hellothere']"], 6:'', 7:[0x20, "['jimbojones']"], ..., 15:'', 16:'' ] (17 positions)
   // serialization RLP for this node: ed8080808080ce208ccb8a68656c6c6f746865726580ce208ccb8a6a696d626f6a6f6e6573808080808080808080
   // hash for this node: 002615b7c405f6f346329a284e8fb248e735cffa89432daba29e56e414df6c30

   vbyte rlp2(shelper::HexToBytes("ed8080808080ce208ccb8a68656c6c6f746865726580ce208ccb8a6a696d626f6a6f6e6573808080808080808080"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp2), shelper::HexToBytes("002615b7c405f6f346329a284e8fb248e735cffa89432daba29e56e414df6c30"));

   // a root extension-even node consumes 010102 and moves to this node
   // root: [0x00010102, 0xd52faf1fde4f21753e2633685f2bac3ff1f32ab72933ece9d59f32ca6f63956d]
   // serialization of this node: e68400010102a0d52faf1fde4f21753e2633685f2bac3ff1f32ab72933ece9d59f32ca6f63956d
   // hash of this node: fcb2e3098029e816b04d99d7e1bba22d7b77336f9fe8604f2adfb04bcf04a727

   vbyte rlp3(shelper::HexToBytes("e68400010102a0d52faf1fde4f21753e2633685f2bac3ff1f32ab72933ece9d59f32ca6f63956d"));
   EXPECT_EQ(crypto.Sha3Keccak(rlp3), shelper::HexToBytes("fcb2e3098029e816b04d99d7e1bba22d7b77336f9fe8604f2adfb04bcf04a727"));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Neo_Leaf_neo)
{
   // insert pair ("neo" => "smarteconomy")
   // neo -> 6e656f / smarteconomy -> 736d61727465636f6e6f6d79
   // Leaf Node: [ '0x206e656f', '0x736d61727465636f6e6f6d79' ]
   // path is encoded (leaf-even 'neo')
   // value represents a string 'smarteconomy'
   // raw node is: 0204206e656f0c736d61727465636f6e6f6d79
   // node hash is: cb787e430f8728a4b3019a8e71ce1f9db51e9051397221f217772055fcda0ba2
   std::vector<vbyte> raw_node(2);
   raw_node[0] = { 0x20, 0x6e, 0x65, 0x6f };                                     // 0x20 + 'neo' (leaf-even)
   raw_node[1] = shelper::HexToBytes(shelper::ASCIIToHexString("smarteconomy")); // 736d61727465636f6e6f6d79

   EXPECT_EQ(vhelper::ToHexString(raw_node[0]), "206e656f");
   EXPECT_EQ(vhelper::ToHexString(raw_node[1]), "736d61727465636f6e6f6d79");

   vbyte bytes;
   BinaryWriter writer(bytes);
   writer.Write(raw_node);

   EXPECT_EQ(vhelper::ToHexString(bytes), "0204206e656f0c736d61727465636f6e6f6d79");

   BinaryReader reader(bytes);
   std::vector<vbyte> node2 = reader.ReadArrays(); // TODO: move to serializable MPTNode and avoid this method
   EXPECT_EQ(raw_node, node2);

   Crypto crypto;
   EXPECT_EQ(crypto.Hash256(bytes), shelper::HexToBytes("cb787e430f8728a4b3019a8e71ce1f9db51e9051397221f217772055fcda0ba2"));
}

TEST(MerklePatriciaTrieTests, Test_MPT_Neo_Branch_3)
{
   // neo -> 6e656f / neoresearch -> 6e656f7265736561726368 / neopt -> 6e656f7074
   // Branch Node (on positions 0,17): [ 0:'', 1:'', ... , 6:'', 7:some_hash ..., 15:'', 16:'smarteconomy' ] (17 positions)
   // Node 7 is "some_hash", as defined above: 2684b232f56b47207c66c49624ac980d18f0aa23d1e81cfc2aa3187a59815990
   // Index 16 is a key serialized RLP for 'smarteconomy': 736d61727465636f6e6f6d79 (size 12, 0x0c)
   // serialization for this node is: 1200000000000000012684b232f56b47207c66c49624ac980d18f0aa23d1e81cfc2aa3187a5981599000000000000000000c736d61727465636f6e6f6d79
   // hash of this node is: f4cf1e4719f29f04a33c8d4273d2423c7baed9dee53ede6c168b13cc7765415e

   // node type 18: 0x12

   Crypto crypto;
   vbyte branchLeaf(shelper::HexToBytes("1200000000000000012684b232f56b47207c66c49624ac980d18f0aa23d1e81cfc2aa3187a5981599000000000000000000c736d61727465636f6e6f6d79"));
   std::cout << "NODE1 BRANCH: " << vhelper::ToHexString(crypto.Hash256(branchLeaf)) << std::endl;
   EXPECT_EQ(crypto.Hash256(branchLeaf), shelper::HexToBytes("f4cf1e4719f29f04a33c8d4273d2423c7baed9dee53ede6c168b13cc7765415e"));

   // if you follow path 6e656f7* you get
   // 6e656f-7-0-74[0x2074, 'test'] => 020220740474657374
   // 6e656f-7-2-65736561726368[0x2065736561726368, 'community] => 0208206573656172636809636f6d6d756e697479
   // Branch Node Size 3 (0x04) (on positions 0,2): [ 0:[0x2074, 'test'] 1:'', 2:[0x2065736561726368, 'community'] ] (3 positions)
   // serialization for this node: 04020220740474657374000208206573656172636809636f6d6d756e697479
   // hash for this node: 2684b232f56b47207c66c49624ac980d18f0aa23d1e81cfc2aa3187a59815990

   vbyte node2(shelper::HexToBytes("04020220740474657374000208206573656172636809636f6d6d756e697479"));
   //std::cout << "NODE2 HASH: " << vhelper::ToHexString(crypto.Hash256(node2)) << std::endl;
   EXPECT_EQ(crypto.Hash256(node2), shelper::HexToBytes("2684b232f56b47207c66c49624ac980d18f0aa23d1e81cfc2aa3187a59815990"));

   // a root extension-even node consumes 010102 and moves to this node
   // root: [0x006e656f, f4cf1e4719f29f04a33c8d4273d2423c7baed9dee53ede6c168b13cc7765415e]
   // serialization of this node: 0204006e656ff4cf1e4719f29f04a33c8d4273d2423c7baed9dee53ede6c168b13cc7765415e
   // hash of this node:

   vbyte nodeRoot(shelper::HexToBytes("0204006e656ff4cf1e4719f29f04a33c8d4273d2423c7baed9dee53ede6c168b13cc7765415e"));
   //std::cout << "ROOT HASH: " << vhelper::ToHexString(crypto.Hash256(nodeRoot)) << std::endl;
   EXPECT_EQ(crypto.Hash256(nodeRoot), shelper::HexToBytes("c6e4fbb40ace933c9b6d693bf02e37c2259325f0197413fd3a7a0691e377f27b"));
}



// neo -> 6e656f
// neoresearch -> 6e656f7265736561726368
// neopt -> 6e656f7074
// neogas -> 6e656f676173
// neoresearchcommunity -> 6e656f7265736561726368636f6d6d756e697479
// community -> 636f6d6d756e697479
