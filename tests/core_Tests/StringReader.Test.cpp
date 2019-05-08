#include <gtest/gtest.h>

// core includes
#include <system/StringReader.hpp>
#include <system/shelper.h>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(StringReaderTests, Test_StringReader_Peek_twice_ok)
{
   StringReader reader("abcd");
   EXPECT_EQ(reader.Peek(), 'a');
   EXPECT_EQ(reader.Peek(), 'a');
}

TEST(StringReaderTests, Test_StringReader_Read_twice_ok)
{
   StringReader reader("abcd");
   EXPECT_EQ(reader.Read(), 'a');
   EXPECT_EQ(reader.Read(), 'b');
}

TEST(StringReaderTests, Test_StringReader_Peak_and_Read)
{
   StringReader reader("abcd");
   EXPECT_EQ(reader.Peek(), 'a'); // do not consume
   EXPECT_EQ(reader.Read(), 'a'); // consume
   EXPECT_EQ(reader.Read(), 'b'); // consume
   EXPECT_EQ(reader.Peek(), 'c'); // do not consume
}

TEST(StringReaderTests, Test_StringReader_ReadCount)
{
   StringReader reader("abcdef");
   char* buffer = new char[4];
   reader.Read(buffer, 0, 4);
   EXPECT_EQ(buffer[0], 'a');
   EXPECT_EQ(buffer[1], 'b');
   EXPECT_EQ(buffer[2], 'c');
   EXPECT_EQ(buffer[3], 'd');
   delete[] buffer;
}
