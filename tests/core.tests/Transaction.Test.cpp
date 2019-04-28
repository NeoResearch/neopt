#include<gtest/gtest.h>

// core includes
#include<payloads/Transaction.hpp>
#include<system/vhelper.hpp>
#include<system/BinaryReader.hpp>

using namespace std;
using namespace neopt;

TEST(TransactionTests, Test_Transaction_Deserialize_MinerTx_SingleFromBlock_Manually)
{
	//////// 010000d11f7a2800000000
	
	string block2tn = "010000d11f7a2800000000";

	vbyte param = shelper::HexToBytes(block2tn);

	BinaryReader reader(param);
	EXPECT_EQ(reader.AvailableBytes(), 11);

	//Transaction* tx = Transaction::DeserializeFrom(reader);
	// doing this manually

	int txCount = reader.ReadVarInt(100000); // TODO: fix max
	EXPECT_EQ(txCount, 1);
	EXPECT_EQ(reader.AvailableBytes(), 10);

	byte txType = reader.ReadByte();
	EXPECT_EQ(txType, 0); // MinerTx
	EXPECT_EQ(reader.AvailableBytes(), 9);

	// transaction->DeserializeUnsignedWithoutType(reader);
	// doing this manually too

	byte TxVersion = reader.ReadByte();
	EXPECT_EQ(TxVersion, 0);
	EXPECT_EQ(reader.AvailableBytes(), 8);

	// DeserializeExclusiveData(reader);
	// doing this manually too
	// this method will come from MinerTransaction
	// d11f7a28 (rest is 00000000)

	uint Nonce = reader.ReadUInt32();
	EXPECT_EQ(Nonce, 679092177);
	EXPECT_EQ(reader.AvailableBytes(), 4);


	// read attributes array 
	// 00 
    vector<TransactionAttribute> Attributes = reader.ReadSerializableArray<TransactionAttribute>(16);
	EXPECT_EQ(Attributes.size(), 0);
	EXPECT_EQ(reader.AvailableBytes(), 3);

	// read inputs array
	// 00
    vector<CoinReference> Inputs = reader.ReadSerializableArray<CoinReference>();
	EXPECT_EQ(Inputs.size(), 0);
	EXPECT_EQ(reader.AvailableBytes(), 2);

	// read outputs array
	// 00
    vector<TransactionOutput> Outputs = reader.ReadSerializableArray<TransactionOutput>();
	EXPECT_EQ(Outputs.size(), 0);
	EXPECT_EQ(reader.AvailableBytes(), 1);

	// finishes the Read Unsigned No type... back to DeserializeFrom 

	// read witness array
	// 00 (last)
	vector<Witness> Witnesses = reader.ReadSerializableArray<Witness>();
	EXPECT_EQ(Witnesses.size(), 0);
	EXPECT_EQ(reader.AvailableBytes(), 0);

	// finishes Tx deserialization
}

TEST(TransactionTests, Test_Transaction_Deserialize_SingleFromBlock_Automatically)
{
	// Miner Transaction
	string block2tn = "0000d11f7a2800000000";

	vbyte param = shelper::HexToBytes(block2tn);

	BinaryReader reader(param);
	EXPECT_EQ(reader.AvailableBytes(), 10);

	Transaction* tx = Transaction::DeserializeFrom(reader);

	EXPECT_EQ(reader.AvailableBytes(), 0);
}

TEST(TransactionTests, Test_Transaction_MinerTx_DeserializeSerialize)
{
	// Miner Transaction
	string block2tn = "0000d11f7a2800000000";

	vbyte param = shelper::HexToBytes(block2tn);

	BinaryReader reader(param);
	EXPECT_EQ(reader.AvailableBytes(), 10);

	Transaction* tx = Transaction::DeserializeFrom(reader);
	EXPECT_EQ(reader.AvailableBytes(), 0);

	vbyte dest;
	BinaryWriter writer(dest);
	tx->Serialize(writer);
	EXPECT_EQ(writer.CountBytes(), 10);
	EXPECT_EQ(dest.size(), 10);

	EXPECT_EQ(param.size(), 10);
	EXPECT_EQ(dest, param); // same hexstring
}


TEST(TransactionTests, Test_Transaction_Deserialize_ContractTx_TestNetBlock74_Manually)
{
	//////// 800000014a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd0000019b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50000c16ff286230067f97110a66136d38badc7b9f88eab013027ce4901fd04014099546819767644bbef323e428aab48c8801e66b8c7fb452dcd11205c13f5b198c9b37e9aa6808d6c3a74e50931d3413115e2a86a4a4a99fcae894219c092ca6340a0de35bc6c04c25b8f6cca46b91a35144db40fc94967293500f08c58df81f7c9ecb59cc13bcaca4d932e27a8d9a8204f48d488b6ccdfccd830c22bf4b7353dd64039346418372b541dfe7fdc99611bfc59cee881044da2912cb2404b885c6472310a2b771153e6a0022abb11aa41288ef98a2aed1bb42714fa6a1c6e85e415b8bb4045cc681dbe07155b554b0291f0352546223e49e3192c221249c29eb97651aec3c5f2f6adfc85a87cfdfef3a15d57391cf99190e8d80b01fcc1ebf8f48c745957f154210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae
	
	string block2tn = "800000014a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd0000019b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50000c16ff286230067f97110a66136d38badc7b9f88eab013027ce4901fd04014099546819767644bbef323e428aab48c8801e66b8c7fb452dcd11205c13f5b198c9b37e9aa6808d6c3a74e50931d3413115e2a86a4a4a99fcae894219c092ca6340a0de35bc6c04c25b8f6cca46b91a35144db40fc94967293500f08c58df81f7c9ecb59cc13bcaca4d932e27a8d9a8204f48d488b6ccdfccd830c22bf4b7353dd64039346418372b541dfe7fdc99611bfc59cee881044da2912cb2404b885c6472310a2b771153e6a0022abb11aa41288ef98a2aed1bb42714fa6a1c6e85e415b8bb4045cc681dbe07155b554b0291f0352546223e49e3192c221249c29eb97651aec3c5f2f6adfc85a87cfdfef3a15d57391cf99190e8d80b01fcc1ebf8f48c745957f154210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae";

	vbyte param = shelper::HexToBytes(block2tn);

	BinaryReader reader(param);
	EXPECT_EQ(reader.AvailableBytes(), 605);

   // 80
	byte txType = reader.ReadByte();
	EXPECT_EQ(txType, 0x80); // ContractTx
	EXPECT_EQ(reader.AvailableBytes(), 604);

	// transaction->DeserializeUnsignedWithoutType(reader);
	// doing this manually too

   // 00
	byte TxVersion = reader.ReadByte();
	EXPECT_EQ(TxVersion, 0);
	EXPECT_EQ(reader.AvailableBytes(), 603);

	// DeserializeExclusiveData(reader);
	// doing this manually too (nothing to do)
	// rest is: 00014a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd0000019b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50000c16ff286230067f97110a66136d38badc7b9f88eab013027ce4901fd04014099546819767644bbef323e428aab48c8801e66b8c7fb452dcd11205c13f5b198c9b37e9aa6808d6c3a74e50931d3413115e2a86a4a4a99fcae894219c092ca6340a0de35bc6c04c25b8f6cca46b91a35144db40fc94967293500f08c58df81f7c9ecb59cc13bcaca4d932e27a8d9a8204f48d488b6ccdfccd830c22bf4b7353dd64039346418372b541dfe7fdc99611bfc59cee881044da2912cb2404b885c6472310a2b771153e6a0022abb11aa41288ef98a2aed1bb42714fa6a1c6e85e415b8bb4045cc681dbe07155b554b0291f0352546223e49e3192c221249c29eb97651aec3c5f2f6adfc85a87cfdfef3a15d57391cf99190e8d80b01fcc1ebf8f48c745957f154210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae

	// nothing on exclusive data for ContractTransaction

	// read attributes array 
	// 00 
   vector<TransactionAttribute> Attributes = reader.ReadSerializableArray<TransactionAttribute>(16);
	EXPECT_EQ(Attributes.size(), 0);
	EXPECT_EQ(reader.AvailableBytes(), 602);

	// read inputs array
	// 01 4a4dfb91023b1b2086029e03af739d9ceab35fffa8d528de9a6fee3e62bbecbd 0000 
   vector<CoinReference> Inputs = reader.ReadSerializableArray<CoinReference>();
	EXPECT_EQ(Inputs.size(), 1);
	EXPECT_EQ(Inputs[0].PrevHash.ToString(), "0xbdecbb623eee6f9ade28d5a8ff5fb3ea9c9d73af039e0286201b3b0291fb4d4a");
	EXPECT_EQ(Inputs[0].PrevIndex, 0);
	EXPECT_EQ(reader.AvailableBytes(), 567);

	// rest is: 019b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc50000c16ff286230067f97110a66136d38badc7b9f88eab013027ce4901fd04014099546819767644bbef323e428aab48c8801e66b8c7fb452dcd11205c13f5b198c9b37e9aa6808d6c3a74e50931d3413115e2a86a4a4a99fcae894219c092ca6340a0de35bc6c04c25b8f6cca46b91a35144db40fc94967293500f08c58df81f7c9ecb59cc13bcaca4d932e27a8d9a8204f48d488b6ccdfccd830c22bf4b7353dd64039346418372b541dfe7fdc99611bfc59cee881044da2912cb2404b885c6472310a2b771153e6a0022abb11aa41288ef98a2aed1bb42714fa6a1c6e85e415b8bb4045cc681dbe07155b554b0291f0352546223e49e3192c221249c29eb97651aec3c5f2f6adfc85a87cfdfef3a15d57391cf99190e8d80b01fcc1ebf8f48c745957f154210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae

	// read outputs array
	// 01 9b7cffdaa674beae0f930ebe6085af9093e5fe56b34a5c220ccdcf6efc336fc5 0000c16ff286230067f97110a66136d38badc7b9f88eab013027ce4901fd04014099546819767644bbef323e428aab48c8801e66b8c7fb452dcd11205c13f5b198c9b37e9aa6808d6c3a74e50931d3413115e2a86a4a4a99fcae894219c092ca6340a0de35bc6c04c25b8f6cca46b91a35144db40fc94967293500f08c58df81f7c9ecb59cc13bcaca4d932e27a8d9a8204f48d488b6ccdfccd830c22bf4b7353dd64039346418372b541dfe7fdc99611bfc59cee881044da2912cb2404b885c6472310a2b771153e6a0022abb11aa41288ef98a2aed1bb42714fa6a1c6e85e415b8bb4045cc681dbe07155b554b0291f0352546223e49e3192c221249c29eb97651aec3c5f2f6adfc85a87cfdfef3a15d57391cf99190e8d80b01fcc1ebf8f48c745957f154210209e7fd41dfb5c2f8dc72eb30358ac100ea8c72da18847befe06eade68cebfcb9210327da12b5c40200e9f65569476bbff2218da4f32548ff43b6387ec1416a231ee821034ff5ceeac41acf22cd5ed2da17a6df4dd8358fcb2bfb1a43208ad0feaab2746b21026ce35b29147ad09e4afe4ec4a7319095f08198fa8babbe3c56e970b143528d2221038dddc06ce687677a53d54f096d2591ba2302068cf123c1f2d75c2dddc542557921039dafd8571a641058ccc832c5e2111ea39b09c0bde36050914384f7a48bce9bf92102d02b1873a0863cd042cc717da31cea0d7cf9db32b74d4c72c01b0011503e2e2257ae
	std::cout << "WILL READ OUTPUTS" << std::endl;
   vector<TransactionOutput> Outputs = reader.ReadSerializableArray<TransactionOutput>();
	EXPECT_EQ(Outputs.size(), 1);
	EXPECT_EQ(Outputs[0].AssetId.ToString(), "0xc56f33fc6ecfcd0c225c4ab356fee59390af8560be0e930faebe74a6daff7c9b");
	EXPECT_EQ(Outputs[0].Value.ToString(), "");
	EXPECT_EQ(Outputs[0].ScriptHash.ToString(), "0");	
	EXPECT_EQ(reader.AvailableBytes(), 1);

	// finishes the Read Unsigned No type... back to DeserializeFrom 

	// read witness array
	// 00 (last)
	vector<Witness> Witnesses = reader.ReadSerializableArray<Witness>();
	EXPECT_EQ(Witnesses.size(), 0);
	EXPECT_EQ(reader.AvailableBytes(), 0);

	// finishes Tx deserialization
}
