#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

// neopt core part
#include<Types.h>
#include<IBinaryReader.h>
#include<IBinaryWriter.h>

namespace neopt
{

class ISerializable
{
public:
   // TODO: what's the best serialization format?

   virtual void DeserializeUnsigned(IBinaryReader& reader) = 0;

   virtual void SerializeUnsigned(IBinaryWriter& writer) = 0;

};

}

#endif
