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
   // Hash160 = SHA256 + RIPEMD160
   virtual vbyte Hash160(const vbyte& message) = 0;
   //{
   //   return RIPEMD160(SHA256(message));
   //}

   // Hash256 = SHA256 + SHA256
   virtual vbyte Hash256(const vbyte& message)
   {
      return SHA256(SHA256(message));
   }

   // Verify signature against public key on elliptic curve NIST P-256 (secp256r1)
   virtual bool VerifySignature(const vbyte& message, const vbyte& signature, const vbyte& pubkey) = 0;

   // -----------------------------------------------------
   // not available on Neo ICrypto, but important for usage
   // -----------------------------------------------------

   virtual vbyte Sign(const vbyte& message, const vbyte& prikey, const vbyte& pubkey)
   {
      // TODO: implement
      return vbyte(0);
   }

   // SHA256
   virtual vbyte SHA256(const vbyte& message) = 0;

   // RIPEMD160
   //virtual vbyte RIPEMD160(const vbyte& message) = 0;
};

}

#endif
