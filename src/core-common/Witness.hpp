#ifndef WITNESS_H
#define WITNESS_H

// system includes

// core includes
#include <crypto/chelper.hpp>
#include <json/JObject.hpp>
#include <numbers/UInt160.hpp>
#include <system/ISerializable.h>
#include <system/types.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class Witness : public ISerializable
{
public:
   vbyte InvocationScript;
   vbyte VerificationScript;

private:
   UInt160* _scriptHash;

public:
   virtual UInt160& getScriptHash()
   {
      if (_scriptHash == nullptr) {
         _scriptHash = new UInt160(chelper::ToScriptHash(VerificationScript));
      }
      return *_scriptHash;
   }

   int Size() const
   {
      return vhelper::GetVarSize(InvocationScript) + vhelper::GetVarSize(InvocationScript);
   }

   //private: // WHY PRIVATE?
public:
   // ISerializable class
   virtual void Deserialize(IBinaryReader& reader)
   {
      InvocationScript = reader.ReadVarBytes(65536);
      VerificationScript = reader.ReadVarBytes(65536);
   }

   // ISerializable class
   virtual void Serialize(IBinaryWriter& writer) const
   {
      writer.WriteVarBytes(InvocationScript);
      writer.WriteVarBytes(VerificationScript);
   }

public:
   JObject ToJson()
   {
      JObject json;
      json["invocation"] = vhelper::ToHexString(InvocationScript);
      json["verification"] = vhelper::ToHexString(VerificationScript);
      return json;
   }
};

}

#endif
