#include<gtest/gtest.h>

// core includes
#include<system/BinaryReader.hpp>
#include<system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(BinaryReaderTest, Test_ReadByte_0x02)
{
	vbyte param(1, 2); // 0x02
	BinaryReader reader(param);
   byte b = reader.ReadByte();
	EXPECT_EQ(b, 0x02);
}

TEST(BinaryReaderTest, Test_ReadByte_0x0102030405)
{
	vbyte param = {0x01, 0x02, 0x03, 0x04, 0x05};
	BinaryReader reader(param);
	EXPECT_EQ(reader.ReadByte(), 0x01);
	EXPECT_EQ(reader.ReadByte(), 0x02);
	EXPECT_EQ(reader.ReadByte(), 0x03);
	EXPECT_EQ(reader.ReadByte(), 0x04);
	EXPECT_EQ(reader.ReadByte(), 0x05);
}
