#ifndef TRANSACTION_OUTPUT_HPP
#define TRANSACTION_OUTPUT_HPP

// c++ standard part
#include <ostream>
#include <sstream>
#include <vector>

// neopt core part
#include <core/IScriptContainer.h>
#include <core/ISnapshot.h> // TODO: remove if possible
#include <system/ISerializable.h>

#include <Witness.hpp>
#include <crypto/Crypto.h>
#include <numbers/Fixed8.hpp>
#include <numbers/UInt160.hpp>
#include <numbers/UInt256.hpp>
#include <wallets/KeyPair.hpp>

#include <system/BinaryWriter.hpp>

namespace neopt {

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
