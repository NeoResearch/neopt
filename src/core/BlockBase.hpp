#ifndef BLOCK_BASE_HPP
#define BLOCK_BASE_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<IVerifiable.hpp>
//#include<system/IEquatable.h>
//#include<system/IComparable.h>
#include<IInventory.hpp>
#include<numbers/UIntBase.hpp>
#include<numbers/BigInteger.h>
#include<system/shelper.h>
#include<crypto/Crypto.h>
//#include<Transaction.hpp>

namespace neopt
{

   class BlockBase : public IVerifiable
   {
   public:
      uint Version;
      UInt256 PrevHash;
      UInt256 MerkleRoot;
      uint Timestamp;
      uint Index;
      ulong ConsensusData;
      UInt160 NextConsensus;
      Witness witness;

public:


   virtual void Deserialize(IBinaryReader& reader)
   {
      std::cout << "BlockBase::Deserialize" << std::endl;
      BlockBase::DeserializeUnsigned(reader);
      if (reader.ReadByte() != 1)
         NEOPT_EXCEPTION("Format Exception BlockBase::Deserialize");
      std::cout << "Will read witness" << std::endl;
      witness = reader.ReadSerializable<Witness>();
   }

   virtual void DeserializeUnsigned(IBinaryReader& reader)
   {
       std::cout << "BlockBase::DeserializeUnsigned" << std::endl;
       Version = reader.ReadUInt32();
       std::cout << "BlockBase::Will read uint256" << std::endl;
       PrevHash = reader.ReadSerializable<UInt256>();
       std::cout << "PrevHash = " << PrevHash.ToString() << std::endl;
       std::cout << "BlockBase::Will read uint256" << std::endl;
       MerkleRoot = reader.ReadSerializable<UInt256>();
       std::cout << "BlockBase::Will read timestamp" << std::endl;
       Timestamp = reader.ReadUInt32();
       std::cout << "timestamp = " << Timestamp << std::endl;
       std::cout << "BlockBase::Will read index" << std::endl;
       Index = reader.ReadUInt32();
       std::cout << "BlockBase::Will read consensus data" << std::endl;
       ConsensusData = reader.ReadUInt64();
       std::cout << "BlockBase::Will read next consensus uint160" << std::endl;
       NextConsensus = reader.ReadSerializable<UInt160>();
       std::cout << "BlockBase::finished reading" << std::endl;
   }

/*
      // IEquatable
      bool Equals(const Block* other)
      {
         if(other == nullptr)
            return false;
         // (other == nullptr ? false : CompareTo(*other) == 0) // TODO: make shorter?
         return false;//CompareTo(*other) == 0;
      }

      // IScriptContainer
      virtual vbyte GetMessage()
      {
         // TODO: implement
         return vbyte(0);
      }

      // ISerializable
      virtual void Deserialize(IBinaryReader& reader)
      {
         NEOPT_EXCEPTION("Cannot deserialize block yet");
      }

      // IVerifiable
      virtual void DeserializeUnsigned(IBinaryReader& reader)
      {
         NEOPT_EXCEPTION("Cannot deserialize unsigned block yet");
      }

      // IVerifiable
      virtual void SerializeUnsigned(IBinaryWriter& writer)
      {
         NEOPT_EXCEPTION("Cannot serialize unsigned block yet");
      }

      // IVerifiable
      virtual vector<Witness> getWitnesses()
      {
         // TODO: implement
         return vector<Witness>(0);
      }

      // IVerifiable
      virtual vector<UInt160> GetScriptHashesForVerifying(ISnapshot snapshot)
      {
         // TODO: implement
         return vector<UInt160>(0);
      }

      // IInventory
      virtual UInt256 getHash()
      {
         // TODO: implement
         return UInt256();
      }

      // IInventory
      virtual InventoryType getInventoryType()
      {
         return InventoryType::IT_Block;
      }

      // IInventory
      virtual bool Verify(ISnapshot& snapshot)
      {
         // TODO: implement
         return false;
      }


*/
   };
}

#endif
