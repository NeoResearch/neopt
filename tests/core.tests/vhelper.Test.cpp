#include<gtest/gtest.h>

// core includes
#include<system/vhelper.hpp>
#include<system/shelper.h>

using namespace std;
using namespace neopt;

// method ToIOStream does not exist anymore
/*
TEST(BinaryReaderTest, Test_TOIStream_raw_0x02)
{
	vbyte param(1, 2); // 0x02
	istream* in = vhelper::ToIStream(param);
   EXPECT_EQ((*in).good(), true);
   byte b = in->get();
   //(*in) >> b; // do not use formatted input
	EXPECT_EQ(b, 0x02);
   delete in;
}

TEST(BinaryReaderTest, Test_TOIStream_raw_0x0102030405)
{
	vbyte param = {0x01, 0x02, 0x03, 0x04, 0x05};
	istream* in = vhelper::ToIStream(param);
   EXPECT_EQ((*in).good(), true);
   byte b = in->get();
	EXPECT_EQ(b, 0x01);
	EXPECT_EQ(in->get(), 0x02);
	EXPECT_EQ(in->get(), 0x03);
	EXPECT_EQ(in->get(), 0x04);
	EXPECT_EQ(in->get(), 0x05);
   delete in;
}

TEST(BinaryReaderTest, Test_TOIStream_raw_0x0102030405_start_2)
{
	vbyte param = {0x01, 0x02, 0x03, 0x04, 0x05};
	istream* in = vhelper::ToIStream(param, 2);
   EXPECT_EQ((*in).good(), true);
   byte b = in->get();
	EXPECT_EQ(b, 0x03);
	EXPECT_EQ(in->get(), 0x04);
	EXPECT_EQ(in->get(), 0x05);
   delete in;
}

TEST(BinaryReaderTest, Test_TOIStream_HexToBytes_Block2_TN)
{
	string block2tn = "00000000ef1f8f66a16fba100ed760f4ac6aa5a0d0bb8f4a0e92705b106761ef181718b3d0765298ceb5f57de7d2b0dab00ed25be4134706ada2d90adb8b7e3aba323a8e1abd125901000000d11f7a289214bdaff3812db982f3b0089a21a278988efeec6a027b2501fd450140884037dd265cb5f5a54802f53c2c8593b31d5b8a9c0bad4c7e366b153d878989d168080ac36b930036a9eb966b48c70bb41792e698fa021116f27c09643563b840e83ab14404d964a91dbac45f5460e88ad57196b1779478e3475334af8c1b49cd9f0213257895c60b5b92a4800eb32d785cbb39ae1f022528943909fd37deba63403677848bf98cc9dbd8fbfd7f2e4f34471866ea82ca6bffbf0f778b6931483700c17829b4bd066eb04983d3aac0bd46b9c8d03a73a8e714d3119de93cd9522e314054d16853b22014190063f77d9edf6fbccefcf71fffd1234f688823b4e429ae5fa639d0a664c842fbdfcb4d6e21f39d81c23563b92cffa09696d93c95bc4893a6401a43071d00d3e854f7f1f321afa7d5301d36f2195dc1e2643463f34ae637d2b02ae0eb11d4256c507a4f8304cea6396a7fce640f50acb301c2f6336d27717e84f155210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae010000d11f7a2800000000";
	vbyte param = shelper::HexToBytes(block2tn);
	EXPECT_EQ(param[0], 0x00);
	EXPECT_EQ(param[1], 0x00);
	EXPECT_EQ(param[2], 0x00);
	EXPECT_EQ(param[3], 0x00);
	EXPECT_EQ(param[4], 0xef);
	EXPECT_EQ(param[5], 0x1f);
	EXPECT_EQ(param[685], 0x00);

	istream* in = vhelper::ToIStream(param);
   EXPECT_EQ((*in).good(), true);
   byte b = in->get();
	EXPECT_EQ(b, 0x00);
	EXPECT_EQ(in->get(), 0x00);
	EXPECT_EQ(in->get(), 0x00);
	EXPECT_EQ(in->get(), 0x00);
	EXPECT_EQ(in->get(), 0xef);
	EXPECT_EQ(in->get(), 0x1f);
   delete in;
}
*/

TEST(vhelperTests, Test_Where_Even_0x0102030405)
{
	vbyte param = {0x01, 0x02, 0x03, 0x04, 0x05};
   std::function<bool(const byte&)> sel = [](const byte& b){return b % 2 == 0;};

   vbyte v2 = vhelper::Where(param, sel);
	EXPECT_EQ(v2.size(), 2);
   EXPECT_EQ(v2[0], 0x02);
   EXPECT_EQ(v2[1], 0x04);
}

TEST(vhelperTests, Test_ToHexString_0x0102030405)
{
	vbyte param = {0x01, 0x02, 0x03, 0x04, 0x05};
   string s = vhelper::ToHexString(param);

   EXPECT_EQ(s, "0102030405");
}

TEST(vhelperTests, Test_ToHexString_0x01)
{
   byte b = 0x01;
   string s = vhelper::ToHexString(b);

   EXPECT_EQ(s, "01");
}


TEST(vhelperTests, Test_Select_Byte_HexString_0x0102030405)
{
	vbyte param = {0x01, 0x02, 0x03, 0x04, 0x05};
   std::function<string(const byte&)> sel = [](const byte& b) -> string {return vhelper::ToHexString(b);};

   vector<string> v2 = vhelper::Select(param, sel);
	EXPECT_EQ(v2.size(), param.size());
   EXPECT_EQ(v2[0], "01");
   EXPECT_EQ(v2[1], "02");
   EXPECT_EQ(v2[2], "03");
   EXPECT_EQ(v2[3], "04");
   EXPECT_EQ(v2[4], "05");
}


TEST(vhelperTests, Test_Concat)
{
	vbyte param1 = {0x01, 0x02, 0x03};
	vbyte param2 = {0x04, 0x05, 0x06};
	vbyte param3 = vhelper::Concat(param1, param2);
	EXPECT_EQ(vhelper::ToHexString(param3), "010203040506");
}

TEST(vhelperTests, Test_Concat2)
{
	vbyte param1 = {0x01, 0x02, 0x03};
	vbyte param2 = {0x04, 0x05, 0x06};
	vbyte param3 = param1;
	param3.insert(param3.end(), param2.begin(), param2.end());
	EXPECT_EQ(vhelper::Concat(param1, param2), param3);
}


TEST(vhelperTests, Test_vhelper_Skip)
{
	vbyte param1 = {0x01, 0x02, 0x03};
	vbyte param2 = vhelper::Skip(param1, 1);
	vbyte param3 = {0x02, 0x03};
	EXPECT_EQ(param2, param3);
}

TEST(vhelperTests, Test_vhelper_Skip2)
{
	vbyte param1 = {0x01, 0x02, 0x03};
	EXPECT_EQ(vhelper::Skip(param1, 2), vbyte(1,0x03));
}

TEST(vhelperTests, Test_vhelper_Skip10)
{
	vbyte param1 = {0x01, 0x02, 0x03};
	EXPECT_EQ(vhelper::Skip(param1, 10), vbyte(0));
}
