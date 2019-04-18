#ifndef KEY_PAIR_HPP
#define KEY_PAIR_HPP

// c++ standard part
// ... none

// neopt core part
#include<system/types.h>
#include<wallets/ECPoint.hpp>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class KeyPair
{
public:

   vbyte PrivateKey;
   ECPoint PublicKey;

};

}

#endif
