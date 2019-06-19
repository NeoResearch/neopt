#include <gtest/gtest.h>

// core includes
#include <json/JObject.hpp>
#include <json/jhelper.hpp>
#include <system/shelper.h>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(jsonTests, Test_json_Parse_empty_array)
{
   string base = "[]";
   JObject* json = jhelper::Parse(base);
   EXPECT_EQ(json->getValue(), base);
}

TEST(jsonTests, Test_json_Parse_array_simple_number)
{
   string base = "[{\"number\":0}]";
   JObject* json = jhelper::Parse(base);
   EXPECT_EQ(json->getValue(), base);
}

TEST(jsonTests, Test_json_Parse_array_simple_empty_array)
{
   string base = "[{\"subarray\":[]}]";
   JObject* json = jhelper::Parse(base);
   EXPECT_EQ(json->getValue(), base);
}

TEST(jsonTests, Test_json_Parse_array_simple_empty_array_spaced)
{
   string base = "[{\"subarray\":   []}]";
   JObject* json = jhelper::Parse(base);
   EXPECT_EQ(json->getValue(), "[{\"subarray\":[]}]");
}

TEST(jsonTests, Test_json_Parse_block)
{
   string base = "[{\"block\":0,\"size\":0,\"storage\":[]}]";

   JObject* json = jhelper::Parse(base);
   //EXPECT_EQ(shelper::StartsWith("0xabcd", "0x"), true);
   EXPECT_EQ(json->getValue(), base);
}
