#include <gtest/gtest.h>

// core includes
#include <system/shelper.h>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(shelperTests, Test_shelper_StartsWith0x_true)
{
   EXPECT_EQ(shelper::StartsWith("0xabcd", "0x"), true);
}

TEST(shelperTests, Test_shelper_StartsWith0x_false)
{
   EXPECT_EQ(shelper::StartsWith("abcd", "0x"), false);
}

TEST(shelperTests, Test_shelper_StartsWith0x_false2)
{
   EXPECT_EQ(shelper::StartsWith("abcd0x", "0x"), false);
}

TEST(shelperTests, Test_shelper_SubstringFrom0x)
{
   EXPECT_EQ(shelper::Substring("0xabcd", 2), "abcd");
}

TEST(shelperTests, Test_shelper_CharsToHexString_abc)
{
   EXPECT_EQ(shelper::ASCIIToHexString("abc"), "616263");
}

TEST(shelperTests, Test_shelper_ASCIIToHexString_hello)
{
   EXPECT_EQ(shelper::ASCIIToHexString("hello"), "68656c6c6f");
}
