#ifndef NEOPT_COMMON_SYSTEM_BITCONVERTER_HPP
#define NEOPT_COMMON_SYSTEM_BITCONVERTER_HPP

// system includes
#include <fstream>
#include <iostream>
#include <vector>

// neopt core part
#include <system/types.h>
//#include<numbers/nhelper.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class BitConverter
{
public:
   static short ToInt16(vbyte data, int from)
   {
      NEOPT_EXCEPTION("NOT IMPLEMENTED BitConverter::ToInt16");
   }

   static unsigned short ToUInt16(vbyte data, int from)
   {
      NEOPT_EXCEPTION("NOT IMPLEMENTED BitConverter::ToUInt16");
   }

   static int ToInt32(vbyte data, int from)
   {
      NEOPT_EXCEPTION("NOT IMPLEMENTED BitConverter::ToInt32");
   }

   static unsigned ToUInt32(vbyte data, int from)
   {
      NEOPT_EXCEPTION("NOT IMPLEMENTED BitConverter::ToUInt32");
   }
};

} // namespace neopt

#endif // NEOPT_COMMON_SYSTEM_BITCONVERTER_HPP
