#ifndef NEOPT_ISERIALIZABLE_H
#define NEOPT_ISERIALIZABLE_H

// neopt core part
#include "types.h" // necessary for vbyte
//#include<system/IBinaryReader.h> // forward declaration
//#include<system/IBinaryWriter.h> // forward declaration

namespace neopt {

// forward declaration (see end of this file)
class IBinaryReader;
// forward declaration (see end of this file)
class IBinaryWriter;

class ISerializable
{
public:
   // deserializes (build) current class from an input IBinaryReader
   virtual void Deserialize(IBinaryReader& reader) = 0;

   // serializes current class into a IBinaryWriter
   virtual void Serialize(IBinaryWriter& writer) const = 0;

   // converts current class into a byte array
   // it needs to be in a separated compilation unit, since it uses BinaryWriter
   // and BinaryWriter cannot be fully specified here
   virtual vbyte ToArray() const; // from C#: neo.IO.Helper
};
}

// forward declarations
#include "IBinaryReader.h"
#include "IBinaryWriter.h"

#endif
