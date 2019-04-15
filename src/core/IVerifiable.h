#ifndef IVERIFIABLE_H
#define IVERIFIABLE_H

// c++ standard part
#include<vector>

// neopt core part
#include<ISerializable.h>
#include<IScriptContainer.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class IVerifiable : public IScriptContainer, public ISerializable
{
public:


   virtual void DeserializeUnsigned(IBinaryReader reader) = 0;

   virtual void SerializeUnsigned(IBinaryWriter writer) = 0;

};

}

#endif
