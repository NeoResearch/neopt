#ifndef COIN_REFERENCE_HPP
#define COIN_REFERENCE_HPP

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
#include <numbers/UInt160.hpp>
#include <wallets/KeyPair.hpp>

#include <system/IBinaryWriter.h>

namespace neopt {

class CoinReference : public ISerializable
{
public:
   UInt256 PrevHash;
   ushort PrevIndex;

   int Size() const
   {
      return PrevHash.Size() + sizeof(ushort);
   }

   virtual void Deserialize(IBinaryReader& reader)
   {
      PrevHash = reader.ReadSerializable<UInt256>();
      PrevIndex = reader.ReadUInt16();
   }

   virtual void Serialize(IBinaryWriter& writer) const
   {
      writer.Write(PrevHash);
      writer.Write(PrevIndex);
   }
};

}

#endif
