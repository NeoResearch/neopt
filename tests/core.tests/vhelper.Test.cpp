#include<gtest/gtest.h>

// core includes
#include<system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(BinaryReaderTest, Test_TOIStream_raw_0x02)
{
	vbyte param(1, 2); // 0x02
	istream* in = vhelper::ToIStream(param);
   EXPECT_EQ((*in).good(), true);
   byte b;
   (*in) >> b;
	EXPECT_EQ(b, 0x02);
   delete in;
}

TEST(BinaryReaderTest, Test_TOIStream_raw_0x0102030405)
{
	vbyte param = {0x01, 0x02, 0x03, 0x04, 0x05};
	istream* in = vhelper::ToIStream(param);
   EXPECT_EQ((*in).good(), true);
   byte b;
   (*in) >> b;
	EXPECT_EQ(b, 0x01);
   (*in) >> b;
	EXPECT_EQ(b, 0x02);
   (*in) >> b;
	EXPECT_EQ(b, 0x03);
   (*in) >> b;
	EXPECT_EQ(b, 0x04);
   (*in) >> b;
	EXPECT_EQ(b, 0x05);
   delete in;
}
