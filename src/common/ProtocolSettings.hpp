#ifndef PROTOCOL_SETTINGS_HPP
#define PROTOCOL_SETTINGS_HPP

// c++ standard part
// ... none

// neopt core part
#include <numbers/UInt256.hpp>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class ProtocolSettings
{
public:
   static const int AddressVersion = 21;
};

}

#endif
