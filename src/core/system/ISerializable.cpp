#include "ISerializable.h"

// forward declarations
#include "IBinaryReader.h"
#include "IBinaryWriter.h"

// regular declarations
#include "BinaryWriter.hpp"
#include "vhelper.hpp" // can perhaps remove

using namespace std;
using namespace neopt;

vbyte
ISerializable::ToArray() const
{
   vbyte data(0);
   BinaryWriter writer(data);
   //std::cout << "ISerializable::ToArray() will invoke Serialize!" << std::endl;
   this->Serialize(writer);
   //writer.Flush(); // not needed
   //std::cout << "OUTPUT IS: " << vhelper::ToHexString(data) << std::endl;
   return data;
}
