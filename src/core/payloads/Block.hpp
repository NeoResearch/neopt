#ifndef BLOCK_HPP
#define BLOCK_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<system/ISerializable.h>
#include<system/IEquatable.h>
#include<system/IComparable.h>
#include<IInventory.hpp>
#include<numbers/UIntBase.hpp>
#include<numbers/BigInteger.h>
#include<system/shelper.h>
#include<payloads/BlockBase.hpp>
#include<payloads/Transaction.hpp>

namespace neopt
{

   class Block : public BlockBase, public IEquatable<Block>, public IInventory
   {
   public:
      const int MaxTransactionsPerBlock = types::MaxValue<ushort>();

      // Transaction is abstract perhaps?
      std::vector<Transaction*> Transactions;

   private:
      UInt256* _hash; // = nullptr

   public:

      Block() :
         _hash(nullptr)
      {
      }

      virtual ~Block()
      {
         if(_hash != nullptr)
            delete _hash;
         _hash = nullptr;
      }

      // IInventory (Core project includes this on BlockBase ??? must be here on C++...)
      virtual UInt256 getHash()
      {
         const ICrypto& crypto = Crypto::Default();

         if(_hash == nullptr)
            _hash = new UInt256(Crypto::Default().Hash256(IInventory::GetHashData()));
         return *_hash; // can also be reference-based if desired
      }

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
         std::cout << "Block::Deserialize" << std::endl;
         BlockBase::Deserialize(reader);
         std::cout << "Block base finished::Deserialize" << std::endl;

/*
         Transactions = new Transaction[reader.ReadVarInt(MaxTransactionsPerBlock)];
            if (Transactions.Length == 0) throw new FormatException();
            HashSet<UInt256> hashes = new HashSet<UInt256>();
            for (int i = 0; i < Transactions.Length; i++)
            {
                Transactions[i] = Transaction.DeserializeFrom(reader);
                if (i == 0)
                {
                    if (Transactions[0].Type != TransactionType.MinerTransaction)
                        throw new FormatException();
                }
                else
                {
                    if (Transactions[i].Type == TransactionType.MinerTransaction)
                        throw new FormatException();
                }
                if (!hashes.Add(Transactions[i].Hash))
                    throw new FormatException();
            }
            if (MerkleTree.ComputeRoot(Transactions.Select(p => p.Hash).ToArray()) != MerkleRoot)
            throw new FormatException();
*/
         NEOPT_EXCEPTION("Cannot deserialize block yet");
      }

      //using BlockBase::DeserializeUnsigned; // TODO: why not get this automatically?
      //     perhaps, a side-effect of IVerifiable virtual inheritance
      // IVerifiable (only on BlockBase)

      virtual void DeserializeUnsigned(IBinaryReader& reader)
      {
         NEOPT_EXCEPTION("SHOULD NEVER CALL Block::DeserializeUnsigned. Strange!");
         BlockBase::DeserializeUnsigned(reader);
      }




      // IVerifiable
      virtual void SerializeUnsigned(IBinaryWriter& writer) const
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
      virtual vector<UInt160> GetScriptHashesForVerifying(ISnapshot& snapshot)
      {
         // TODO: implement
         return vector<UInt160>(0);
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



   };
}

#endif
