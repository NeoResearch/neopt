#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

// neopt core part
#include<system/types.h>
#include<system/IBinaryReader.h>
#include<system/IBinaryWriter.h>

namespace neopt
{

class ISerializable
{
public:
   // TODO: what's the best serialization format?

   virtual void Deserialize(IBinaryReader& reader) = 0;
   /*
   virtual void DeserializeUnsigned(IBinaryReader& reader) = 0;

   virtual void SerializeUnsigned(IBinaryWriter& writer) = 0;
   */

};

}

#endif
