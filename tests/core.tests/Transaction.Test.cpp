#include<gtest/gtest.h>

// core includes
#include<payloads/Transaction.hpp>
#include<system/vhelper.hpp>
#include<system/BinaryReader.hpp>

using namespace std;
using namespace neopt;

TEST(TransactionTests, Test_Transaction_Deserialize_SingleFromBlock_Manually)
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
