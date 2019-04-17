#ifndef IBINARYWRITER_H
#define IBINARYWRITER_H

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

// neopt core part
#include<system/types.h>

namespace neopt
{

class IBinaryWriter
{
public:
   // writes data directly from vector
   virtual void Write(const vector<byte>& data) = 0;

   virtual void Write(long v) = 0;

   // writes var bytes on vector
   virtual void WriteVarBytes(vbyte& v) = 0;
};

}

#endif
