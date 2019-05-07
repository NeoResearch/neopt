#include <gtest/gtest.h>

// core includes
#include <json/JObject.hpp>
#include <system/shelper.h>
#include <system/vhelper.hpp>
#include <json/jhelper.hpp>

using namespace std;
using namespace neopt;

TEST(jsonTests, Test_json_Parse_block)
{
   string base = "[{\"block\":0,\"size\":0,\"storage\": []},]";

   JObject* json = jhelper::Parse(base); 
   //EXPECT_EQ(shelper::StartsWith("0xabcd", "0x"), true);
   EXPECT_EQ(1,2);
}

