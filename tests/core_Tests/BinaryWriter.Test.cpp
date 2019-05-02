#include <gtest/gtest.h>

// core includes
#include <system/BinaryReader.hpp>
#include <system/BinaryWriter.hpp>
#include <system/vhelper.hpp>

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
   vbyte bytes = { 0x01, 0x02, 0x03, 0x04, 0x05 };
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

TEST(BinaryWriterReaderTests, Test_WriteReadInt16)
{
   vbyte vdata;
   BinaryWriter writer(vdata);
   int16 val = -1;
   writer.Write(val);

   BinaryReader reader(vdata);
   int16 val2 = reader.ReadInt16();
   EXPECT_EQ(val, val2);
}

TEST(BinaryWriterReaderTests, Test_WriteReadInt32)
{
   vbyte vdata;
   BinaryWriter writer(vdata);
   int32 val = -1;
   writer.Write(val);

   BinaryReader reader(vdata);
   int32 val2 = reader.ReadInt32();
   EXPECT_EQ(val, val2);
}

TEST(BinaryWriterReaderTests, Test_WriteReadInt64)
{
   vbyte vdata;
   BinaryWriter writer(vdata);
   long val = -1;
   writer.Write(val);

   BinaryReader reader(vdata);
   long val2 = reader.ReadInt64();
   EXPECT_EQ(val, val2);
}

TEST(BinaryWriterReaderTests, Test_WriteReadUInt64_0x0102030405060708)
{
   vbyte vdata;
   BinaryWriter writer(vdata);
   ulong val = 72623859790382856L;
   writer.Write(val);
   
   EXPECT_EQ(vdata[0], 0x08);
   EXPECT_EQ(vdata[1], 0x07);
   EXPECT_EQ(vdata[2], 0x06);
   EXPECT_EQ(vdata[3], 0x05);
   EXPECT_EQ(vdata[4], 0x04);
   EXPECT_EQ(vdata[5], 0x03);
   EXPECT_EQ(vdata[6], 0x02);
   EXPECT_EQ(vdata[7], 0x01);
   BinaryReader reader(vdata);
   ulong val2 = reader.ReadUInt64();
   EXPECT_EQ(val, val2);
   //vbyte vdata = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
}
