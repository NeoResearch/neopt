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
