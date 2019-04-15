#ifndef IVERIFIABLE_H
#define IVERIFIABLE_H

// c++ standard part
#include<vector>

// neopt core part
#include<system/ISerializable.h>
#include<IScriptContainer.h>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt160.hpp>
#include<Witness.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class IVerifiable : public IScriptContainer, public ISerializable
{
public:

   virtual vector<Witness> getWitnesses() = 0;

   // TODO: if possible, remove ISnapshot from here
   virtual vector<UInt160> GetScriptHashesForVerifying(ISnapshot snapshot) = 0;

   virtual void DeserializeUnsigned(IBinaryReader& reader) = 0;

   virtual void SerializeUnsigned(IBinaryWriter& writer) = 0;

};

}

#endif
