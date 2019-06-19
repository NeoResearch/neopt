#ifndef IVERIFIABLE_H
#define IVERIFIABLE_H

// c++ standard part
#include <ostream>
#include <sstream>
#include <vector>

// neopt core part
// vscode intellisense bug: 'ISerializable' not found with angled notation, use quotes instead... (???)
#include <system/ISerializable.h>
#include "IScriptContainer.h"
#include "ISnapshot.h" // TODO: remove if possible

#include <Witness.hpp>
#include <crypto/Crypto.h>
#include <numbers/UInt160.hpp>
#include <wallets/KeyPair.hpp>

#include <system/BinaryWriter.hpp>

namespace neopt {

// WARNING: escaping from the "Diamond of Death"
// making ISerializable a virtual inheritance
class IVerifiable : public IScriptContainer
  , virtual public ISerializable
{
public:
   virtual std::vector<Witness> getWitnesses() = 0;

   // TODO: if possible, remove ISnapshot from here
   virtual std::vector<UInt160> GetScriptHashesForVerifying(ISnapshot& snapshot) = 0;

   virtual void DeserializeUnsigned(IBinaryReader& reader) = 0;

   virtual void SerializeUnsigned(IBinaryWriter& writer) const = 0;

   // originally from Wallets/Helper.cs
   virtual vbyte Sign(const KeyPair& key) const
   {
      return Crypto::Default().Sign(this->GetHashData(), key.PrivateKey, vhelper::Skip(key.PublicKey.EncodePoint(false), 1));
   }

   // originally from Network/P2P/Helper.cs
   virtual vbyte GetHashData() const
   {
      //std::ostringstream oss;
      vbyte data;
      BinaryWriter writer(data);
      std::cout << "will write data on IVerifiable SerializeUnsigned" << std::endl;
      this->SerializeUnsigned(writer);
      return std::move(data);
      //return vhelper::ToArray(oss);
   }
};

}

#endif
