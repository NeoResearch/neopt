#include <gtest/gtest.h>

// core includes
#include <ledger/payloads/Block.hpp>
#include <system/BinaryReader.hpp>
#include <system/printable.h>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

TEST(BlockDeserializeTest, Test_Block_ManualBaseDeserialize_WarmUp)
{
   string block2tn = "00000000ef1f8f66a16fba100ed760f4ac6aa5a0d0bb8f4a0e92705b106761ef181718b3";
   vbyte param = shelper::HexToBytes(block2tn);
   EXPECT_EQ(param[0], 0x00);
   EXPECT_EQ(param[3], 0x00);
   EXPECT_EQ(param[4], 0xef);
   EXPECT_EQ(param[5], 0x1f);
   EXPECT_EQ(param[6], 0x8f);
   EXPECT_EQ(param[7], 0x66);
   EXPECT_EQ(param[8], 0xa1);
   EXPECT_EQ(param[9], 0x6f);

   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 36);
   EXPECT_EQ(reader.Good(), true);

   uint Version = reader.ReadUInt32();
   EXPECT_EQ(Version, 0);
   EXPECT_EQ(reader.AvailableBytes(), 32);
   UInt256 PrevHash = reader.ReadSerializable<UInt256>();
   EXPECT_EQ(PrevHash.ToString(), "0xb3181718ef6167105b70920e4a8fbbd0a0a56aacf460d70e10ba6fa1668f1fef");
   EXPECT_EQ(reader.AvailableBytes(), 0);
}

TEST(BlockDeserializeTest, Test_Block_ManualDeserialize_Including_Base_TestNet2)
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

   // STILL ON BASE
   // STRANGE NUMBER 1
   // 01
   byte one = reader.ReadByte();
   EXPECT_EQ(one, 0x01);
   EXPECT_EQ(reader.AvailableBytes(), 581);

   // NEEDS TO DESERIALIZE WITNESS NOW
   /* fd450140884037dd265cb5f5a54802f53c2c8593b31d5b8a9c0bad4c7e366b153d878989d168080ac36b930036a9eb966b48c70bb41792e698fa021116f27c09643563b840e83ab14404d964a91dbac45f5460e88ad57196b1779478e3475334af8c1b49cd9f0213257895c60b5b92a4800eb32d785cbb39ae1f022528943909fd37deba63403677848bf98cc9dbd8fbfd7f2e4f34471866ea82ca6bffbf0f778b6931483700c17829b4bd066eb04983d3aac0bd46b9c8d03a73a8e714d3119de93cd9522e314054d16853b22014190063f77d9edf6fbccefcf71fffd1234f688823b4e429ae5fa639d0a664c842fbdfcb4d6e21f39d81c23563b92cffa09696d93c95bc4893a6401a43071d00d3e854f7f1f321afa7d5301d36f2195dc1e2643463f34ae637d2b02ae0eb11d4256c507a4f8304cea6396a7fce640f50acb301c2f6336d27717e84f155210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae	*/
   // Don't need to do this manually... Witness.Test will do this
   Witness witness = reader.ReadSerializable<Witness>();
   EXPECT_EQ(witness.InvocationScript.size(), 325);
   //std::cout << "Invocation:" << vhelper::ToHexString(witness.InvocationScript) << std::endl;
   // 40884037dd265cb5f5a54802f53c2c8593b31d5b8a9c0bad4c7e366b153d878989d168080ac36b930036a9eb966b48c70bb41792e698fa021116f27c09643563b840e83ab14404d964a91dbac45f5460e88ad57196b1779478e3475334af8c1b49cd9f0213257895c60b5b92a4800eb32d785cbb39ae1f022528943909fd37deba63403677848bf98cc9dbd8fbfd7f2e4f34471866ea82ca6bffbf0f778b6931483700c17829b4bd066eb04983d3aac0bd46b9c8d03a73a8e714d3119de93cd9522e314054d16853b22014190063f77d9edf6fbccefcf71fffd1234f688823b4e429ae5fa639d0a664c842fbdfcb4d6e21f39d81c23563b92cffa09696d93c95bc4893a6401a43071d00d3e854f7f1f321afa7d5301d36f2195dc1e2643463f34ae637d2b02ae0eb11d4256c507a4f8304cea6396a7fce640f50acb301c2f6336d27717e84
   EXPECT_EQ(witness.VerificationScript.size(), 241);
   //std::cout << "Verification:" << vhelper::ToHexString(witness.VerificationScript) << std::endl;
   // 55210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae
   EXPECT_EQ(reader.AvailableBytes(), 11);

   // the rest for tx is: 010000d11f7a2800000000

   // 01
   //reader.ReadVarInt(MaxTransactionsPerBlock)
   ushort countTx = reader.ReadVarInt(types::MaxValue<ushort>());
   EXPECT_EQ(countTx, 1);
   EXPECT_EQ(reader.AvailableBytes(), 10);

   // move to Transaction::DeserializeFrom

   Transaction* tx = Transaction::DeserializeFrom(reader);
   EXPECT_EQ(tx->Type, TransactionType::TT_MinerTransaction);
   EXPECT_EQ(reader.AvailableBytes(), 0);

   // REST OF THE BLOCK
   /*


	 010000d11f7a2800000000";

	*/

   // FULL
   /*
	00000000ef1f8f66a16fba100ed760f4ac6aa5a0d0bb8f4a0e92705b106761ef181718b3d0765298ceb5f57de7d2b0dab00ed25be4134706ada2d90adb8b7e3aba323a8e1abd125901000000d11f7a289214bdaff3812db982f3b0089a21a278988efeec6a027b25
	01
	fd450140884037dd265cb5f5a54802f53c2c8593b31d5b8a9c0bad4c7e366b153d878989d168080ac36b930036a9eb966b48c70bb41792e698fa021116f27c09643563b840e83ab14404d964a91dbac45f5460e88ad57196b1779478e3475334af8c1b49cd9f0213257895c60b5b92a4800eb32d785cbb39ae1f022528943909fd37deba63403677848bf98cc9dbd8fbfd7f2e4f34471866ea82ca6bffbf0f778b6931483700c17829b4bd066eb04983d3aac0bd46b9c8d03a73a8e714d3119de93cd9522e314054d16853b22014190063f77d9edf6fbccefcf71fffd1234f688823b4e429ae5fa639d0a664c842fbdfcb4d6e21f39d81c23563b92cffa09696d93c95bc4893a6401a43071d00d3e854f7f1f321afa7d5301d36f2195dc1e2643463f34ae637d2b02ae0eb11d4256c507a4f8304cea6396a7fce640f50acb301c2f6336d27717e84f155210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae010000d11f7a2800000000
	*/
}

TEST(BlockDeserializeTest, Test_Block_ManualDeserialize_Including_Base_TestNet74)
{
   string block2tn = "00000000cf9d9c77df2a27eabeaac0b69c282017c328c2da3ec9fbd2ca45b18fdb8cb68a9b6c99d55ac0358b114add3c399357412e9f9878213660dd9daa984332d0e507c5c412594a0000000b5a4046e108122cf3812db982f3b0089a21a278988efeec6a027b2501fd4501405bd82ea1d16a0855c112735a43d83161669b209b1d2d34a2b5c9f744021742ca5671fee68ce62cbe3df2cc231d6ea639fe3d47b70b36b22c8f445b8475069a69405cf8636e0f4e9c4b9e938271e13b020cddd51456c5cb3365a8a052aa03ca5a3cc822e7692907f4b4835b0e237d5cd2a66bda5a1e8d127aa80054de775a1e9ebe408013053b4260eabd2ef03ceed72886d60ae756a25c6cbc5e1dccbbbee3ccd8e6e6f139b9b7d8c7361493eb8706bd9d5ad14c7dbbe89b3a2c4be5a8b68f1592f0405df68939bcf0b218b5a67e9f57c00145ade69fd5f54a6fd5221fb5a8e183b611a4569c642ac5c266b2bacea0e7d89725348e2a2c424a95a1fa5007f03a28346940b3d5c4c7b967ff7f975295f38ffe18a7d2d6f376fd7266aecef690333a6569e6f1e492cde85cb49d4b45b31488663ea7850404186afbc108aceb9c0c7862c43ef155210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae0200000b5a404600000000800000014a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd0000019b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50000c16ff286230067f97110a66136d38badc7b9f88eab013027ce4901fd04014099546819767644bbef323e428aab48c8801e66b8c7fb452dcd11205c13f5b198c9b37e9aa6808d6c3a74e50931d3413115e2a86a4a4a99fcae894219c092ca6340a0de35bc6c04c25b8f6cca46b91a35144db40fc94967293500f08c58df81f7c9ecb59cc13bcaca4d932e27a8d9a8204f48d488b6ccdfccd830c22bf4b7353dd64039346418372b541dfe7fdc99611bfc59cee881044da2912cb2404b885c6472310a2b771153e6a0022abb11aa41288ef98a2aed1bb42714fa6a1c6e85e415b8bb4045cc681dbe07155b554b0291f0352546223e49e3192c221249c29eb97651aec3c5f2f6adfc85a87cfdfef3a15d57391cf99190e8d80b01fcc1ebf8f48c745957f154210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae";
   vbyte param = shelper::HexToBytes(block2tn);
   //BinaryReader reader(param);
   //Block B = vhelper::AsSerializable<Block>(param);
   EXPECT_EQ(param[0], 0x00);
   EXPECT_EQ(param[1], 0x00);
   EXPECT_EQ(param[2], 0x00);
   EXPECT_EQ(param[3], 0x00);
   EXPECT_EQ(param[4], 0xcf);
   EXPECT_EQ(param[5], 0x9d);

   BinaryReader reader(param);
   EXPECT_EQ(reader.AvailableBytes(), 1291);

   //00000000
   auto Version = reader.ReadUInt32();
   EXPECT_EQ(Version, 00);
   EXPECT_EQ(reader.AvailableBytes(), 1287);

   //cf9d9c77df2a27eabeaac0b69c282017c328c2da3ec9fbd2ca45b18fdb8cb68a
   //
   auto PrevHash = reader.ReadSerializable<UInt256>();
   EXPECT_EQ(PrevHash.ToString(), "0x8ab68cdb8fb145cad2fbc93edac228c31720289cb6c0aabeea272adf779c9dcf");
   EXPECT_EQ(reader.AvailableBytes(), 1255);

   //9b6c99d55ac0358b114add3c399357412e9f9878213660dd9daa984332d0e507
   //
   auto MerkleRoot = reader.ReadSerializable<UInt256>();
   EXPECT_EQ(MerkleRoot.ToString(), "0x07e5d0324398aa9ddd60362178989f2e415793393cdd4a118b35c05ad5996c9b");
   EXPECT_EQ(reader.AvailableBytes(), 1223);

   // c5c41259
   //
   auto Timestamp = reader.ReadUInt32();
   EXPECT_EQ(Timestamp, 1494402245);
   EXPECT_EQ(reader.AvailableBytes(), 1219);

   // 4a000000
   //
   auto Index = reader.ReadUInt32();
   EXPECT_EQ(Index, 74);
   EXPECT_EQ(reader.AvailableBytes(), 1215);

   // 0b5a4046 e108122c
   //
   auto ConsensusData = reader.ReadUInt64();
   EXPECT_EQ(ConsensusData, 3175610450888907275UL);
   EXPECT_EQ(reader.AvailableBytes(), 1207);

   // f3812db982f3b0089a21a278988efeec6a027b25
   //
   auto NextConsensus = reader.ReadSerializable<UInt160>();
   EXPECT_EQ(NextConsensus.ToString(), "0x257b026aecfe8e9878a2219a08b0f382b92d81f3");
   EXPECT_EQ(reader.AvailableBytes(), 1187);

   //
   // STILL ON BASE
   // STRANGE NUMBER 1
   // 01
   byte one = reader.ReadByte();
   EXPECT_EQ(one, 0x01);
   EXPECT_EQ(reader.AvailableBytes(), 1186);

   //
   // NEEDS TO DESERIALIZE WITNESS NOW
   /* fd450140884037dd265cb5f5a54802f53c2c8593b31d5b8a9c0bad4c7e366b153d878989d168080ac36b930036a9eb966b48c70bb41792e698fa021116f27c09643563b840e83ab14404d964a91dbac45f5460e88ad57196b1779478e3475334af8c1b49cd9f0213257895c60b5b92a4800eb32d785cbb39ae1f022528943909fd37deba63403677848bf98cc9dbd8fbfd7f2e4f34471866ea82ca6bffbf0f778b6931483700c17829b4bd066eb04983d3aac0bd46b9c8d03a73a8e714d3119de93cd9522e314054d16853b22014190063f77d9edf6fbccefcf71fffd1234f688823b4e429ae5fa639d0a664c842fbdfcb4d6e21f39d81c23563b92cffa09696d93c95bc4893a6401a43071d00d3e854f7f1f321afa7d5301d36f2195dc1e2643463f34ae637d2b02ae0eb11d4256c507a4f8304cea6396a7fce640f50acb301c2f6336d27717e84f155210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae	*/
   // Don't need to do this manually... Witness.Test will do this
   Witness witness = reader.ReadSerializable<Witness>();
   EXPECT_EQ(witness.InvocationScript.size(), 325);
   EXPECT_EQ(witness.VerificationScript.size(), 241);
   //std::cout << "Verification:" << vhelper::ToHexString(witness.VerificationScript) << std::endl;
   //
   EXPECT_EQ(reader.AvailableBytes(), 616);

   // the rest for tx is: 0200000b5a404600000000800000014a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd0000019b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50000c16ff286230067f97110a66136d38badc7b9f88eab013027ce4901fd04014099546819767644bbef323e428aab48c8801e66b8c7fb452dcd11205c13f5b198c9b37e9aa6808d6c3a74e50931d3413115e2a86a4a4a99fcae894219c092ca6340a0de35bc6c04c25b8f6cca46b91a35144db40fc94967293500f08c58df81f7c9ecb59cc13bcaca4d932e27a8d9a8204f48d488b6ccdfccd830c22bf4b7353dd64039346418372b541dfe7fdc99611bfc59cee881044da2912cb2404b885c6472310a2b771153e6a0022abb11aa41288ef98a2aed1bb42714fa6a1c6e85e415b8bb4045cc681dbe07155b554b0291f0352546223e49e3192c221249c29eb97651aec3c5f2f6adfc85a87cfdfef3a15d57391cf99190e8d80b01fcc1ebf8f48c745957f154210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae

   // 02
   //reader.ReadVarInt(MaxTransactionsPerBlock)
   ushort countTx = reader.ReadVarInt(types::MaxValue<ushort>());
   EXPECT_EQ(countTx, 2);
   EXPECT_EQ(reader.AvailableBytes(), 615);

   // tx 1: MinerTx
   // 00000b5a404600000000
   // move to Transaction::DeserializeFrom

   std::cout << "WILL READ FIRST TRANSACTION" << std::endl;
   Transaction* tx = Transaction::DeserializeFrom(reader);
   EXPECT_EQ(tx->Type, TransactionType::TT_MinerTransaction);
   EXPECT_EQ(reader.AvailableBytes(), 605);

   // tx 2: ContractTx
   // 800000014a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd0000019b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50000c16ff286230067f97110a66136d38badc7b9f88eab013027ce4901fd04014099546819767644bbef323e428aab48c8801e66b8c7fb452dcd11205c13f5b198c9b37e9aa6808d6c3a74e50931d3413115e2a86a4a4a99fcae894219c092ca6340a0de35bc6c04c25b8f6cca46b91a35144db40fc94967293500f08c58df81f7c9ecb59cc13bcaca4d932e27a8d9a8204f48d488b6ccdfccd830c22bf4b7353dd64039346418372b541dfe7fdc99611bfc59cee881044da2912cb2404b885c6472310a2b771153e6a0022abb11aa41288ef98a2aed1bb42714fa6a1c6e85e415b8bb4045cc681dbe07155b554b0291f0352546223e49e3192c221249c29eb97651aec3c5f2f6adfc85a87cfdfef3a15d57391cf99190e8d80b01fcc1ebf8f48c745957f154210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae
   // move to Transaction::DeserializeFrom

   /*
	std::cout << "WILL READ SECOND TRANSACTION" << std::endl;
	Transaction* tx2 = Transaction::DeserializeFrom(reader);
	EXPECT_EQ(tx2->Type , TransactionType::TT_ContractTransaction);
	EXPECT_EQ(reader.AvailableBytes(), 605);
	*/

   // REST OF THE BLOCK
   /*


	 010000d11f7a2800000000";

	*/

   // FULL
   /*
	00000000ef1f8f66a16fba100ed760f4ac6aa5a0d0bb8f4a0e92705b106761ef181718b3d0765298ceb5f57de7d2b0dab00ed25be4134706ada2d90adb8b7e3aba323a8e1abd125901000000d11f7a289214bdaff3812db982f3b0089a21a278988efeec6a027b25
	01
	fd450140884037dd265cb5f5a54802f53c2c8593b31d5b8a9c0bad4c7e366b153d878989d168080ac36b930036a9eb966b48c70bb41792e698fa021116f27c09643563b840e83ab14404d964a91dbac45f5460e88ad57196b1779478e3475334af8c1b49cd9f0213257895c60b5b92a4800eb32d785cbb39ae1f022528943909fd37deba63403677848bf98cc9dbd8fbfd7f2e4f34471866ea82ca6bffbf0f778b6931483700c17829b4bd066eb04983d3aac0bd46b9c8d03a73a8e714d3119de93cd9522e314054d16853b22014190063f77d9edf6fbccefcf71fffd1234f688823b4e429ae5fa639d0a664c842fbdfcb4d6e21f39d81c23563b92cffa09696d93c95bc4893a6401a43071d00d3e854f7f1f321afa7d5301d36f2195dc1e2643463f34ae637d2b02ae0eb11d4256c507a4f8304cea6396a7fce640f50acb301c2f6336d27717e84f155210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae010000d11f7a2800000000
	*/
}
