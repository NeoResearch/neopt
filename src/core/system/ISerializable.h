#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

// neopt core part
#include<system/types.h>
//#include<system/IBinaryReader.h> // forward declaration
//#include<system/IBinaryWriter.h> // forward declaration

namespace neopt
{

// forward declaration
class IBinaryReader;
// forward declaration
class IBinaryWriter;


class ISerializable
{
public:
   // TODO: what's the best serialization format?

   virtual void Deserialize(IBinaryReader& reader) = 0;

};

}

#endif
