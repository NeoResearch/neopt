#include "ISerializable.h"

// forward declarations
#include "IBinaryReader.h"
#include "IBinaryWriter.h"

// regular declarations
#include "BinaryWriter.hpp"

using namespace std;
using namespace neopt;

vbyte
ISerializable::ToArray() const
{
   vbyte data(0);
   BinaryWriter writer(data);
   this->Serialize(writer);
   return data;
}
