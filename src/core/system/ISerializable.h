#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

// neopt core part
#include<system/types.h>
//#include<system/IBinaryReader.h> // forward declaration
//#include<system/IBinaryWriter.h> // forward declaration

namespace neopt
{

// forward declaration (see end of this file)
class IBinaryReader;
// forward declaration (see end of this file)
class IBinaryWriter;


class ISerializable
{
public:
   // TODO: what's the best serialization format?

   virtual void Deserialize(IBinaryReader& reader) = 0;

   //virtual vbyte ToArray() const = 0;
   virtual void Serialize(IBinaryWriter& writer) const = 0;
   //{
      // TODO: make pure virtual = 0
   //}


};

}

// forward declarations
#include<system/IBinaryReader.h>
#include<system/IBinaryWriter.h>

#endif
