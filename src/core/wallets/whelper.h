#ifndef WHELPER_H
#define WHELPER_H

// Wallet Helper: whelper

// system
#include<vector>
#include<sstream>
#include<limits>

// neo core
#include<system/types.h>
#include<numbers/UInt160.hpp>
#include<IVerifiable.h>
#include<crypto/ICrypto.h>
#include<system/vhelper.h>

namespace neopt
{

// wallets helper class
class whelper
{
public:

   static vbyte Sign(ICrypto& crypto, const IVerifiable& verifiable, const KeyPair& key)
   {
      return crypto.Sign(verifiable.GetHashData(), key.PrivateKey, vhelper::Skip(key.PublicKey.EncodePoint(false), 1));
   }

   static string ToAddress(const ProtocolSettings& settings, const UInt160& scriptHash)
   {
      vbyte data(21);
      data[0] = settings.AddressVersion;
      Buffer.BlockCopy(scriptHash.ToArray(), 0, data, 1, 20);
      return chelper::Base58CheckEncode(data);
   }

   static UInt160 ToScriptHash(const ProtocolSettings& settings, string& address)
   {
      vbyte data = chelper::Base58CheckDecode(address);
      if (data.Length != 21)
          NEOPT_EXCEPTION("Format Exception ToScriptHash");
      if (data[0] != settings.AddressVersion)
          NEOPT_EXCEPTION("Format Exception ToScriptHash");
      return UInt160(vhelper::Skip(data, 1));
   }
};

// TODO: define all operators here that are necessary

}

#endif
