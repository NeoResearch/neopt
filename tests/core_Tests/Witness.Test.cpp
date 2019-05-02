#include<gtest/gtest.h>

// core includes
#include<Witness.hpp>
#include<system/vhelper.hpp>
#include<system/BinaryReader.hpp>

using namespace std;
using namespace neopt;

TEST(WitnessTest, Test_Witness_Deserialize_Two_Empty_Scripts)
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

TEST(WitnessTest, Test_Witness_Deserialize_Array_Two_Empty_Scripts)
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
