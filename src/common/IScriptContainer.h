#ifndef ISCRIPTCONTAINER_H
#define ISCRIPTCONTAINER_H

// c++ standard part
#include <vector>

// neopt core part
#include <system/types.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class IScriptContainer
{
public:
   // use move semantics for "move-based" return (similar to "copy-based")
   virtual vector<byte> GetMessage() = 0;
};

}

#endif
