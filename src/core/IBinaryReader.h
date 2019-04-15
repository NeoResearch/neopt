#ifndef IBINARYREADER_H
#define IBINARYREADER_H

// system includes
#include<vector>

// neopt core part
#include<Types.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class IBinaryReader
{
public:
   // read data directly on vector
   virtual void Read(vector<byte>& data, int begin, int readsize) = 0;
};

}

#endif
