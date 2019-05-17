#include <gtest/gtest.h>
#include<gmock/gmock.h>

// core includes
#include <Witness.hpp>
#include <system/BinaryReader.hpp>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

using ::testing::Return; // testing


TEST(WitnessTests, Test_Witness_Deserialize_Two_Empty_Scripts)
{
   string block2tn = "0000";
   vbyte param = shelper::HexToBytes(block2tn);
   EXPECT_EQ(param[0], 0x00);
   EXPECT_EQ(param[1], 0x00);

   BinaryReader reader(param);
   Witness w = reader.ReadSerializable<Witness>();
   EXPECT_EQ(w.InvocationScript.size(), 0);
   EXPECT_EQ(w.VerificationScript.size(), 0);
}

TEST(WitnessTests, Test_Witness_Deserialize_Array_Two_Empty_Scripts)
{
   string block2tn = "0200000000";
   vbyte param = shelper::HexToBytes(block2tn);
   EXPECT_EQ(param[0], 0x02);

   BinaryReader reader(param);
   vector<Witness> vw = reader.ReadSerializableArray<Witness>();
   EXPECT_EQ(vw.size(), 2);
   EXPECT_EQ(vw[0].InvocationScript.size(), 0);
   EXPECT_EQ(vw[1].VerificationScript.size(), 0);
}

/*
class MockWitness : public Witness
{
public:
   MockInvokeHashTx()
     : Transaction(TT_InvocationTransaction)
   {
   }

   MOCK_METHOD0(getHash, UInt256());

   MOCK_METHOD1(DeserializeExclusiveData, void(IBinaryReader&));
};
*/

   //EXPECT_CALL(mockTx1, getHash())
   //  .WillOnce(Return(UInt256(htx1)));
     //.WillOnce(Return(UInt256(htx1)));


TEST(WitnessTests, Test_Witness_ToArray)
{
   Witness w;
   w.VerificationScript = vbyte(0);
   w.InvocationScript = vbyte(0);
   
   EXPECT_EQ(w.ToArray(), vbyte({0x00, 0x00}));
}
