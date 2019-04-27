#include<gtest/gtest.h>

// core includes
#include<system/BinaryWriter.hpp>
#include<system/BinaryReader.hpp>
#include<system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(BinaryWriterTests, Test_WriteByte)
{
	vbyte vdata;
	BinaryWriter writer(vdata);
	writer.Write((byte)0x02);
	EXPECT_EQ(vdata.size(), 1);
	EXPECT_EQ(vdata[0], 0x02);
}

TEST(BinaryWriterTests, Test_WriteBytes)
{
	vbyte vdata;
	BinaryWriter writer(vdata);
	vbyte bytes = {0x01, 0x02, 0x03, 0x04, 0x05};
	writer.Write(bytes);
	EXPECT_EQ(vdata.size(), 5);
	EXPECT_EQ(vdata[0], 0x01);
	EXPECT_EQ(vdata[1], 0x02);
	EXPECT_EQ(vdata[2], 0x03);
	EXPECT_EQ(vdata[3], 0x04);
	EXPECT_EQ(vdata[4], 0x05);
}


TEST(BinaryWriterTests, Test_WriteUInt32)
{
	vbyte vdata;
	BinaryWriter writer(vdata);
	uint32 val = 16909060; // 0x01020304 (big-endian)
	writer.Write(val);
	EXPECT_EQ(vdata.size(), 4);
	EXPECT_EQ(vdata[0], 0x04);
	EXPECT_EQ(vdata[1], 0x03);
	EXPECT_EQ(vdata[2], 0x02);
	EXPECT_EQ(vdata[3], 0x01);
}

TEST(BinaryWriterReaderTests, Test_WriteReadUInt32)
{
	vbyte vdata;
	BinaryWriter writer(vdata);
	uint32 val = 16909060; // 0x01020304 (big-endian)
	writer.Write(val);

	BinaryReader reader(vdata);
	uint32 val2 = reader.ReadUInt32();
	EXPECT_EQ(val, val2);
}
