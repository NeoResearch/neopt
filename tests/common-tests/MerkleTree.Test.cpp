#include <gtest/gtest.h>

// core includes
#include <adt/MerkleTree.hpp>

using namespace std;
using namespace neopt;

TEST(MerkleTreeTest, Test_MerkleRoot_TN74)
{
   // TestNet 74

   // tx1 : minertx
   UInt256 hTx1 = UInt256::Parse("0xf2195b0382fca1d8648fe0f9bdbf441ac4f651f614bfbf5d92ba842a9698e9f1");

   // tx2: contracttx
   UInt256 hTx2 = UInt256::Parse("0x4feb0081f9425cab84269127bef0a871a84d4408f09923d17ebb257cd231b362");

   vector<UInt256> hashes = { hTx1, hTx2 };
   UInt256 calcRoot = MerkleTree::ComputeRoot(hashes);

   EXPECT_EQ(calcRoot.ToString(), "0x07e5d0324398aa9ddd60362178989f2e415793393cdd4a118b35c05ad5996c9b");
}
