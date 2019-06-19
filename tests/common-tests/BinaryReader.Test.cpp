//#include<gtest/gtest.h>
#include <gtest/gtest.h>

// core includes
#include <system/BinaryReader.hpp>
#include <system/types.h>
#include <system/vhelper.hpp>

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
   vbyte param = { 0x01, 0x02, 0x03, 0x04, 0x05 };
   BinaryReader reader(param);
   EXPECT_EQ(reader.ReadByte(), 0x01);
   EXPECT_EQ(reader.ReadByte(), 0x02);
   EXPECT_EQ(reader.ReadByte(), 0x03);
   EXPECT_EQ(reader.ReadByte(), 0x04);
   EXPECT_EQ(reader.ReadByte(), 0x05);
}

TEST(BinaryReaderTest, Test_AvailableBytes_0x02)
{
   vbyte param(1, 2); // 0x02
   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 1);
}

TEST(BinaryReaderTest, Test_AvailableBytes_0x0102030405)
{
   vbyte param = { 0x01, 0x02, 0x03, 0x04, 0x05 };
   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 5);
}

TEST(BinaryReaderTest, Test_ReadByteAndAvailable_0x0102030405)
{
   vbyte param = { 0x01, 0x02, 0x03, 0x04, 0x05 };
   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 5);
   EXPECT_EQ(reader.ReadByte(), 0x01);
   EXPECT_EQ(reader.ReadByte(), 0x02);
   EXPECT_EQ(reader.ReadByte(), 0x03);
   EXPECT_EQ(reader.AvailableBytes(), 2);
}

TEST(BinaryReaderTest, Test_Read_Middle_Full_0x0102030405)
{
   vbyte source = { 0x01, 0x02, 0x03, 0x04, 0x05 };
   vbyte param = { 0x07, 0x08, 0x09 };
   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 3);
   reader.Read(source, 0, 3);
   EXPECT_EQ(reader.AvailableBytes(), 0);
   // source should be: 0x01 0x07 0x08 0x04 0x05
   EXPECT_EQ(source.size(), 5);
   EXPECT_EQ(source[0], 0x07);
   EXPECT_EQ(source[1], 0x08);
   EXPECT_EQ(source[2], 0x09);
   EXPECT_EQ(source[3], 0x04);
   EXPECT_EQ(source[4], 0x05);
}

TEST(BinaryReaderTest, Test_Read_Middle_0x0102030405)
{
   vbyte source = { 0x01, 0x02, 0x03, 0x04, 0x05 };
   vbyte param = { 0x07, 0x08, 0x09 };
   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 3);
   reader.Read(source, 1, 2); // reader has 3 bytes {0x07, 0x08, 0x09}
   EXPECT_EQ(reader.AvailableBytes(), 1);
   // source should be: 0x01 0x07 0x08 0x04 0x05
   EXPECT_EQ(source.size(), 5);
   EXPECT_EQ(reader.AvailableBytes(), 1);
   EXPECT_EQ(reader.ReadByte(), 0x09);
   EXPECT_EQ(source[0], 0x01);
   EXPECT_EQ(source[1], 0x07);
   EXPECT_EQ(source[2], 0x08);
   EXPECT_EQ(source[3], 0x04);
   EXPECT_EQ(source[4], 0x05);
}

TEST(BinaryReaderTest, Test_Read_All_0x010203)
{
   vbyte source(3, 0);
   vbyte param = { 0x01, 0x02, 0x03 };
   BinaryReader reader(param);
   reader.Read(source, 0, source.size());
   // source should be: 0x01 0x02 0x03
   EXPECT_EQ(source.size(), 3);
   EXPECT_EQ(reader.AvailableBytes(), 0);
   EXPECT_EQ(source[0], 0x01);
   EXPECT_EQ(source[1], 0x02);
   EXPECT_EQ(source[2], 0x03);
}

TEST(BinaryReaderTest, Test_Read_All_UInt64_0x0102030405060708)
{
   vbyte param = { 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01 };
   BinaryReader reader(param);
   ulong val = reader.ReadUInt64();
   EXPECT_EQ(val, 72623859790382856L);
}
