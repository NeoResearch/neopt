#include <gtest/gtest.h>

// core includes
#include <ledger/payloads/BlockBase.hpp>
#include <system/BinaryReader.hpp>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(BlockDeserializeTest, Test_BlockBase_ManualBaseDeserialize)
{
   string block2tn = "00000000ef1f8f66a16fba100ed760f4ac6aa5a0d0bb8f4a0e92705b106761ef181718b3d0765298ceb5f57de7d2b0dab00ed25be4134706ada2d90adb8b7e3aba323a8e1abd125901000000d11f7a289214bdaff3812db982f3b0089a21a278988efeec6a027b2501fd450140884037dd265cb5f5a54802f53c2c8593b31d5b8a9c0bad4c7e366b153d878989d168080ac36b930036a9eb966b48c70bb41792e698fa021116f27c09643563b840e83ab14404d964a91dbac45f5460e88ad57196b1779478e3475334af8c1b49cd9f0213257895c60b5b92a4800eb32d785cbb39ae1f022528943909fd37deba63403677848bf98cc9dbd8fbfd7f2e4f34471866ea82ca6bffbf0f778b6931483700c17829b4bd066eb04983d3aac0bd46b9c8d03a73a8e714d3119de93cd9522e314054d16853b22014190063f77d9edf6fbccefcf71fffd1234f688823b4e429ae5fa639d0a664c842fbdfcb4d6e21f39d81c23563b92cffa09696d93c95bc4893a6401a43071d00d3e854f7f1f321afa7d5301d36f2195dc1e2643463f34ae637d2b02ae0eb11d4256c507a4f8304cea6396a7fce640f50acb301c2f6336d27717e84f155210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae010000d11f7a2800000000";
   vbyte param = shelper::HexToBytes(block2tn);
   //BinaryReader reader(param);
   //Block B = vhelper::AsSerializable<Block>(param);
   EXPECT_EQ(param[0], 0x00);
   EXPECT_EQ(param[1], 0x00);
   EXPECT_EQ(param[2], 0x00);
   EXPECT_EQ(param[3], 0x00);
   EXPECT_EQ(param[4], 0xef);
   EXPECT_EQ(param[5], 0x1f);
   EXPECT_EQ(param[685], 0x00);

   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 686);

   //00000000
   auto Version = reader.ReadUInt32();
   EXPECT_EQ(Version, 00);
   EXPECT_EQ(reader.AvailableBytes(), 682);

   //ef1f8f66a16fba100ed760f4ac6aa5a0d0bb8f4a0e92705b106761ef181718b3
   auto PrevHash = reader.ReadSerializable<UInt256>();
   EXPECT_EQ(PrevHash.ToString(), "0xb3181718ef6167105b70920e4a8fbbd0a0a56aacf460d70e10ba6fa1668f1fef");
   EXPECT_EQ(reader.AvailableBytes(), 650);

   //d0765298ceb5f57de7d2b0dab00ed25be4134706ada2d90adb8b7e3aba323a8e
   auto MerkleRoot = reader.ReadSerializable<UInt256>();
   EXPECT_EQ(MerkleRoot.ToString(), "0x8e3a32ba3a7e8bdb0ad9a2ad064713e45bd20eb0dab0d2e77df5b5ce985276d0");
   EXPECT_EQ(reader.AvailableBytes(), 618);

   // 1abd1259
   auto Timestamp = reader.ReadUInt32();
   EXPECT_EQ(Timestamp, 1494400282);
   EXPECT_EQ(reader.AvailableBytes(), 614);

   // 01000000
   auto Index = reader.ReadUInt32();
   EXPECT_EQ(Index, 1);
   EXPECT_EQ(reader.AvailableBytes(), 610);

   // d11f7a28 9214bdaf
   auto ConsensusData = reader.ReadUInt64();
   EXPECT_EQ(ConsensusData, 12663300345212575697UL);
   EXPECT_EQ(reader.AvailableBytes(), 602);

   // f3812db982f3b0089a21a278988efeec6a027b25
   auto NextConsensus = reader.ReadSerializable<UInt160>();
   EXPECT_EQ(NextConsensus.ToString(), "0x257b026aecfe8e9878a2219a08b0f382b92d81f3");
   EXPECT_EQ(reader.AvailableBytes(), 582);

   // REST OF THE BLOCK
   /*

	 01fd450140884037dd265cb5f5a54802f53c2c8593b31d5b8a9c0bad4c7e366b153d878989d168080ac36b930036a9eb966b48c70bb41792e698fa021116f27c09643563b840e83ab14404d964a91dbac45f5460e88ad57196b1779478e3475334af8c1b49cd9f0213257895c60b5b92a4800eb32d785cbb39ae1f022528943909fd37deba63403677848bf98cc9dbd8fbfd7f2e4f34471866ea82ca6bffbf0f778b6931483700c17829b4bd066eb04983d3aac0bd46b9c8d03a73a8e714d3119de93cd9522e314054d16853b22014190063f77d9edf6fbccefcf71fffd1234f688823b4e429ae5fa639d0a664c842fbdfcb4d6e21f39d81c23563b92cffa09696d93c95bc4893a6401a43071d00d3e854f7f1f321afa7d5301d36f2195dc1e2643463f34ae637d2b02ae0eb11d4256c507a4f8304cea6396a7fce640f50acb301c2f6336d27717e84f155210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae010000d11f7a2800000000";

	*/
}
