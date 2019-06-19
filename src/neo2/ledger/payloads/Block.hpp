#ifndef BLOCK_HPP
#define BLOCK_HPP

// c++ standard part
#include <unordered_set>
#include <vector>

// neopt core part
#include <core/IInventory.hpp>
#include <numbers/BigInteger.h>
#include <numbers/UIntBase.hpp>
#include <ledger/payloads/BlockBase.hpp>
#include <ledger/payloads/Transaction.hpp>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/ISerializable.h>
#include <system/shelper.h>
//#include<payloads/TransactionFactory.h>
#include <adt/MerkleTree.hpp>
#include <system/HashSet.hpp>

namespace neopt {

class Block : public BlockBase
  , public IEquatable<Block>
  , public IInventory
{
public:
   const int MaxTransactionsPerBlock = types::MaxValue<ushort>();

   // Transaction is abstract perhaps?
   std::vector<Transaction*> Transactions;

private:
   UInt256* _hash; // = nullptr

public:
   Block()
     : _hash(nullptr)
   {
   }

   virtual ~Block()
   {
      if (_hash != nullptr)
         delete _hash;
      _hash = nullptr;
   }

   // IInventory (Core project includes this on BlockBase ??? must be here on C++...)
   virtual UInt256 getHash()
   {
      const ICrypto& crypto = Crypto::Default();

      if (_hash == nullptr)
         _hash = new UInt256(Crypto::Default().Hash256(IInventory::GetHashData()));
      return *_hash; // can also be reference-based if desired
   }

   // IEquatable
   bool Equals(const Block* other)
   {
      if (other == nullptr)
         return false;
      // (other == nullptr ? false : CompareTo(*other) == 0) // TODO: make shorter?
      return false; //CompareTo(*other) == 0;
   }

   // IScriptContainer
   virtual vbyte GetMessage()
   {
      // TODO: implement
      return vbyte(0);
   }

   // TODO: create faster and better hashes
   struct uintbase_hash
   {
      std::size_t operator()(const UIntBase& _node) const
      {
         return std::hash<std::string>()(_node.ToString());
      }
   };

   // ISerializable
   virtual void Deserialize(IBinaryReader& reader)
   {
      std::cout << "Block::Deserialize" << std::endl;
      BlockBase::Deserialize(reader);
      std::cout << "Block base finished::Deserialize" << std::endl;

      Transactions = std::vector<Transaction*>(reader.ReadVarInt(MaxTransactionsPerBlock), nullptr);
      if (Transactions.size() == 0)
         NEOPT_EXCEPTION("Block Deserialize FormatException");
      std::cout << "TRANSACTION SIZE = " << Transactions.size() << std::endl;

      //std::unordered_set<UInt256, uintbase_hash> hashes;
      HashSet<UInt256> hashes;
      //HashSet<UInt256> hashes = new HashSet<UInt256>();
      for (int i = 0; i < Transactions.size(); i++) {
         // not as easy as first thought...
         // needs a factory together with a deserialization builder
         Transactions[i] = Transaction::DeserializeFrom(reader); //new Transaction(Transaction.DeserializeFrom(reader);

         std::cout << "Block:: TX Deserialized" << std::endl;
         if (i == 0) {
            if (Transactions[0]->Type != TransactionType::TT_MinerTransaction)
               NEOPT_EXCEPTION("Block First Miner Tx Format Exception");
            //throw new FormatException();
         } else {
            if (Transactions[i]->Type == TransactionType::TT_MinerTransaction)
               NEOPT_EXCEPTION("Block Miner Tx Format Exception");
            //throw new FormatException();
         }
         //hashes.emplace(Transactions[i]->getHash());
         //if (!hashes->emplace(Transactions[i]->getHash()).second)
         if (!hashes.Add(Transactions[i]->getHash()))
            NEOPT_EXCEPTION("Block HashSet.Add Format Exception");
         //throw new FormatException();
      }

      // note that const will be removed because we trust that getHash() only updates useful stuff
      std::function<UInt256(const Transaction*)> sel = [](const Transaction* t) -> UInt256 { return (const_cast<Transaction*>(t))->getHash(); };
      //         std::function<UInt256(const Transaction*&)> sel = [](const Transaction*& t) -> UInt256{return (const_cast<Transaction*&>(t))->getHash();};
      UInt256 calcRoot = MerkleTree::ComputeRoot(vhelper::SelectP(Transactions, sel));
      if (calcRoot != MerkleRoot) {
         std::cout << "Difference: calcRoot {" << calcRoot.ToString() << "} merkle {" << MerkleRoot.ToString() << "}" << std::endl;
         NEOPT_EXCEPTION("Block ComputeRoot FormatException");
      }
      std::cout << "PASSED FROM Merkle" << std::endl;
      //throw new FormatException();

      //NEOPT_EXCEPTION("Cannot deserialize block yet");
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

   virtual void Serialize(IBinaryWriter& writer) const
   {
      NEOPT_EXCEPTION("Serialize not implemented for Block");
   }
};
}

#endif
