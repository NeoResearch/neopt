#ifndef IVERIFIABLE_H
#define IVERIFIABLE_H

// c++ standard part
#include<vector>

// neopt core part
#include<system/ISerializable.h>
#include<IScriptContainer.h>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt160.hpp>
#include<Witness.hpp>
#include<wallets/KeyPair.hpp>
#include<crypto/ICrypto.h>

namespace neopt
{

// WARNING: escaping from the "Diamond of Death"
// making ISerializable a virtual inheritance
class IVerifiable : public IScriptContainer, virtual public ISerializable
{
public:

   virtual std::vector<Witness> getWitnesses() = 0;

   // TODO: if possible, remove ISnapshot from here
   virtual std::vector<UInt160> GetScriptHashesForVerifying(ISnapshot& snapshot) = 0;

   virtual void DeserializeUnsigned(IBinaryReader& reader) = 0;

   virtual void SerializeUnsigned(IBinaryWriter& writer) = 0;

   // originally from Wallets/Helper.cs
   virtual vbyte Sign(ICrypto& crypto, const KeyPair& key) const
   {
      return crypto.Sign(this->GetHashData(), key.PrivateKey, vhelper::Skip(key.PublicKey.EncodePoint(false), 1));
   }

   // originally from Network/P2P/Helper.cs
   virtual vbyte GetHashData() const
   {
      // TODO: implement
      return vbyte(0);
   }
   /*
   public static byte[] GetHashData(this IVerifiable verifiable)
   {
       using (MemoryStream ms = new MemoryStream())
       using (BinaryWriter writer = new BinaryWriter(ms))
       {
           verifiable.SerializeUnsigned(writer);
           writer.Flush();
           return ms.ToArray();
       }
   }
   */

};

}

#endif
