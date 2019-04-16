#ifndef ICRYPTO_H
#define ICRYPTO_H

// system includes
// none ..

// core includes
#include<system/types.h>


namespace neopt
{

class ICrypto
{
public:
   virtual vbyte Hash160(const vbyte& message) = 0;

   virtual vbyte Hash256(const vbyte& message) = 0;

   virtual bool VerifySignature(const vbyte& message, const byte& signature, const byte& pubkey) = 0;
};

}

#endif
