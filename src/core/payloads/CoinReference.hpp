#ifndef COIN_REFERENCE_HPP
#define COIN_REFERENCE_HPP

// c++ standard part
#include<vector>
#include<ostream>
#include<sstream>

// neopt core part
#include<system/ISerializable.h>
#include<IScriptContainer.h>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt160.hpp>
#include<Witness.hpp>
#include<wallets/KeyPair.hpp>
#include<crypto/Crypto.h>

#include<system/IBinaryWriter.h>


namespace neopt
{

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
