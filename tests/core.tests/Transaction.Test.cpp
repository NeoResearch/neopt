#include<gtest/gtest.h>

// core includes
#include<payloads/Transaction.hpp>
#include<system/vhelper.hpp>
#include<system/BinaryReader.hpp>

using namespace std;
using namespace neopt;

TEST(TransactionTests, Test_Transaction_Deserialize_SingleFromBlock_Manually)
{
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
	// nothing to read
	EXPECT_EQ(reader.AvailableBytes(), 8);
	// d11f7a2800000000

	// reading attributes
	//vector<TransactionAttributes> Attributes = reader.ReadSerializableArray<TransactionAttribute>(16); // TODO: fix limit
	// manually (FOR NOW)

	int count = reader.ReadVarInt(16);
	EXPECT_EQ(count, 0);
	EXPECT_EQ(reader.AvailableBytes(), 9);

	//vector<T> array(this->ReadVarInt((ulong)max)); // TODO: why ulong?



	EXPECT_EQ(reader.AvailableBytes(), 0);
}

TEST(TransactionTests, Test_Transaction_Deserialize_SingleFromBlock_Automatically)
{
	string block2tn = "010000d11f7a2800000000";

	vbyte param = shelper::HexToBytes(block2tn);

	BinaryReader reader(param);
	EXPECT_EQ(reader.AvailableBytes(), 11);

	Transaction* tx = Transaction::DeserializeFrom(reader);

	EXPECT_EQ(reader.AvailableBytes(), 0);
}
