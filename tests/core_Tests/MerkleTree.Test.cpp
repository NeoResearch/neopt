#include <gtest/gtest.h>

#include <gmock/gmock.h> // will need mocking here for Tx

// core includes
#include <adt/MerkleTree.hpp>
#include <payloads/Transaction.hpp>
#include <system/shelper.h>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

using ::testing::Return; // testing

// must move this to Utils in the future
class MockInvokeHashTx : public Transaction
{
public:
   MockInvokeHashTx()
     : Transaction(TT_InvocationTransaction)
   {
   }

   MOCK_METHOD0(getHash, UInt256());

   MOCK_METHOD1(DeserializeExclusiveData, void(IBinaryReader&));
};

TEST(MerkleTreeTest, Test_MerkleRoot_TN74)
{
   // TestNet 74

   MockInvokeHashTx mockTx1;

   vbyte htx1 = shelper::HexToBytes("07e5d0324398aa9ddd60362178989f2e415793393cdd4a118b35c05ad5996c9b");

   EXPECT_CALL(mockTx1, getHash())
     .WillOnce(Return(UInt256(htx1)));
     //.WillOnce(Return(UInt256(htx1)));

   EXPECT_EQ(mockTx1.getHash().ToString(), "0x9b6c99d55ac0358b114add3c399357412e9f9878213660dd9daa984332d0e507");

   //auto MerkleRoot = reader.ReadSerializable<UInt256>();
   //EXPECT_EQ(MerkleRoot.ToString(), "0x07e5d0324398aa9ddd60362178989f2e415793393cdd4a118b35c05ad5996c9b");
   //EXPECT_EQ(1, 2);
}
 