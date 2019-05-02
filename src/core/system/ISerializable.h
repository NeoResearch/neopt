#ifndef NEOPT_ISERIALIZABLE_H
#define NEOPT_ISERIALIZABLE_H

// neopt core part
#include "types.h"
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
   virtual void Deserialize(IBinaryReader& reader) = 0;

   virtual void Serialize(IBinaryWriter& writer) const = 0;
};
}

// forward declarations
#include "IBinaryReader.h"
#include "IBinaryWriter.h"

#endif
