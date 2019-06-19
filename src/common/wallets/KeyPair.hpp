#ifndef KEY_PAIR_HPP
#define KEY_PAIR_HPP

// KeyPair is originally part of the C# spec Neo.Wallets namespace
// KeyPair consists of a private/public key pair

// c++ standard part
// ... none

// neopt core part
#include <crypto/ecc/ECPoint.hpp>
#include <system/types.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class KeyPair
{
public:
   vbyte PrivateKey;
   ECPoint PublicKey;
};

}

#endif
