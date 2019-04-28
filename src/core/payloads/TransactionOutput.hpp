#ifndef TRANSACTION_OUTPUT_HPP
#define TRANSACTION_OUTPUT_HPP

// c++ standard part
#include<vector>
#include<ostream>
#include<sstream>

// neopt core part
#include<system/ISerializable.h>
#include<IScriptContainer.h>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt256.hpp>
#include<numbers/UInt160.hpp>
#include<numbers/Fixed8.hpp>
#include<Witness.hpp>
#include<wallets/KeyPair.hpp>
#include<crypto/Crypto.h>

#include<system/BinaryWriter.hpp>


namespace neopt
{

// WARNING: escaping from the "Diamond of Death"
// making ISerializable a virtual inheritance
class TransactionOutput : public ISerializable
{
public:

   UInt256 AssetId;
   Fixed8 Value;
   UInt160 ScriptHash;

   int Size() const
   {
      return AssetId.Size() + Value.Size() + ScriptHash.Size();
   } 

   void Deserialize(IBinaryReader& reader)
   {
      this->AssetId = reader.ReadSerializable<UInt256>();
      this->Value = reader.ReadSerializable<Fixed8>();

      // TODO: compare this!! operator<= for Fixed8
      //if (Value <= Fixed8::Zero()) 
      //   NEOPT_EXCEPTION("TransactionOutput Deserialize FormatException");
      this->ScriptHash = reader.ReadSerializable<UInt160>();
   }

   void Serialize(IBinaryWriter& writer) const
   {
      writer.Write(AssetId);
      writer.Write(Value);
      writer.Write(ScriptHash);
   }


};

}

#endif
