#ifndef BUFFER_HPP
#define BUFFER_HPP

// system includes
// none ..

// core includes
#include <system/types.h>

namespace neopt {

class Buffer
{
public:
   // this copy should overwrite data on destination (not append) // TODO: use memcpy over vector data
   static void BlockCopy(const vbyte& src, int srcOffset, vbyte& dst, int dstOffset, int count)
   {
      // srcOffset: The zero-based byte offset into src

      NEOPT_EXCEPTION("Not Implemented BlockCopy");
   }
};

}

#endif
