#include <gtest/gtest.h>

// core includes
#include <system/shelper.h>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(vhelperTests, Test_Where_Even_0x0102030405)
{
   vbyte param = { 0x01, 0x02, 0x03, 0x04, 0x05 };
   std::function<bool(const byte&)> sel = [](const byte& b) { return b % 2 == 0; };

   vbyte v2 = vhelper::Where(param, sel);
   EXPECT_EQ(v2.size(), 2);
   EXPECT_EQ(v2[0], 0x02);
   EXPECT_EQ(v2[1], 0x04);
}

TEST(vhelperTests, Test_ToHexString_0x0102030405)
{
   vbyte param = { 0x01, 0x02, 0x03, 0x04, 0x05 };
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
   vbyte param = { 0x01, 0x02, 0x03, 0x04, 0x05 };
   std::function<string(const byte&)> sel = [](const byte& b) -> string { return vhelper::ToHexString(b); };

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
   vbyte param1 = { 0x01, 0x02, 0x03 };
   vbyte param2 = { 0x04, 0x05, 0x06 };
   vbyte param3 = vhelper::Concat(param1, param2);
   EXPECT_EQ(vhelper::ToHexString(param3), "010203040506");
}

TEST(vhelperTests, Test_Concat2)
{
   vbyte param1 = { 0x01, 0x02, 0x03 };
   vbyte param2 = { 0x04, 0x05, 0x06 };
   vbyte param3 = param1;
   param3.insert(param3.end(), param2.begin(), param2.end());
   EXPECT_EQ(vhelper::Concat(param1, param2), param3);
}

TEST(vhelperTests, Test_Concat_Empty1)
{
   vbyte param1 = { 0x01, 0x02, 0x03 };
   vbyte param2 = {};
   vbyte param3 = vhelper::Concat(param1, param2);
   EXPECT_EQ(param3, param1);
}

TEST(vhelperTests, Test_Concat_Empty2)
{
   vbyte param1 = {};
   vbyte param2 = { 0x04, 0x05, 0x06 };
   vbyte param3 = vhelper::Concat(param1, param2);
   EXPECT_EQ(vhelper::ToHexString(param3), "040506");
}

TEST(vhelperTests, Test_vhelper_Skip)
{
   vbyte param1 = { 0x01, 0x02, 0x03 };
   vbyte param2 = vhelper::Skip(param1, 1);
   vbyte param3 = { 0x02, 0x03 };
   EXPECT_EQ(param2, param3);
}

TEST(vhelperTests, Test_vhelper_Skip2)
{
   vbyte param1 = { 0x01, 0x02, 0x03 };
   EXPECT_EQ(vhelper::Skip(param1, 2), vbyte(1, 0x03));
}

TEST(vhelperTests, Test_vhelper_Skip10)
{
   vbyte param1 = { 0x01, 0x02, 0x03 };
   EXPECT_EQ(vhelper::Skip(param1, 10), vbyte(0));
}

TEST(vhelperTests, Test_ToHexString_nibble_0Xa23)
{
   vnibble param = { 0Xa, 0X2, 0X3 };
   string s = vhelper::ToHexString(param);

   EXPECT_EQ(s, "a23");
}

TEST(vhelperTests, Test_ToHexString_one_nibble_0Xa)
{
   nibble n = 0XA;
   string s = vhelper::ToHexString(n);

   EXPECT_EQ(s, "a");
}

TEST(vhelperTests, Test_nibble_byte_size)
{
   nibble n = 0Xa; // half byte does not actually exists
   byte b = 0x0a;

   EXPECT_EQ(sizeof(nibble), 1);
   EXPECT_EQ(sizeof(byte), 1);
   EXPECT_EQ((byte)n, b); // cast is needed
}

TEST(vhelperTests, Test_nibble_NibblesToBytes)
{
   // TODO: rename type... vbyte to bytes?
   vnibble nibbles = { 0Xa, 0X2, 0X3, 0X4 };
   vbyte bytes = vhelper::NibblesToBytes(nibbles);

   EXPECT_EQ(nibbles.size(), 4);
   EXPECT_EQ(bytes.size(), 2);
   EXPECT_EQ(bytes[0], 0xa2);
   EXPECT_EQ(bytes[1], 0x34);
}

TEST(vhelperTests, Test_nibble_NibblesToBytesToNibbles)
{
   vnibble nibbles = { 0Xa, 0X2, 0X3, 0X4 };
   vbyte bytes = vhelper::NibblesToBytes(nibbles);
   vnibble nibbles2 = vhelper::BytesToNibbles(bytes);

   EXPECT_EQ(nibbles, nibbles2);
}

TEST(vhelperTests, Test_nibble_BytesToNibblesToBytes)
{
   vbyte bytes = { 0x01, 0x02, 0x03 };
   vnibble nibbles = vhelper::BytesToNibbles(bytes);
   vbyte bytes2 = vhelper::NibblesToBytes(nibbles);

   EXPECT_EQ(bytes, bytes2);
}


