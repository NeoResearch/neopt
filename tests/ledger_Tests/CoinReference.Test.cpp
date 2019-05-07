#include <gtest/gtest.h>

// core includes
#include <ledger/payloads/CoinReference.hpp>
#include <system/BinaryReader.hpp>
#include <system/BinaryWriter.hpp>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(CoinReferenceTest, Test_CoinReference_Array1_DeserializeSerialize)
{
   string hex = "014a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd0000";

   vbyte param = shelper::HexToBytes(hex);

   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 35);

   vector<CoinReference> Inputs = reader.ReadSerializableArray<CoinReference>();
   EXPECT_EQ(Inputs.size(), 1);
   EXPECT_EQ(Inputs[0].PrevHash.ToString(), "0xbdecbb623eee6f9ade28d5a8ff5fb3ea9c9d73af039e0286201b3b0291fb4d4a");
   EXPECT_EQ(Inputs[0].PrevIndex, 0);
   EXPECT_EQ(reader.AvailableBytes(), 0);

   vbyte dest1;
   BinaryWriter writer1(dest1);
   //std::cout << "WILL CALL Serialize Manually!" << std::endl;
   Inputs[0].Serialize(writer1);
   EXPECT_EQ(writer1.CountBytes(), 34);
   EXPECT_EQ(dest1.size(), 34);
   EXPECT_EQ(vhelper::ToHexString(dest1), "4a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd0000");

   vbyte dest;
   BinaryWriter writer(dest);
   IBinaryWriter::WriteArray<CoinReference>(writer, Inputs);
   EXPECT_EQ(writer.CountBytes(), 35);
   EXPECT_EQ(dest.size(), 35);

   EXPECT_EQ(param.size(), 35);
   EXPECT_EQ(dest, param); // same hexstring
}
