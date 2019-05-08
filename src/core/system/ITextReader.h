#ifndef ITEXTREADER_H
#define ITEXTREADER_H

// system includes
#include <vector>

// neopt core part
#include <system/types.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class ITextReader
{
public:
   virtual char Peek() const = 0;

   virtual char Read() = 0;

   virtual int Read(char* out, int index, int count) = 0;
};
}

#endif
