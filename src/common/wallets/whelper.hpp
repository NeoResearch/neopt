#ifndef WHELPER_HPP
#define WHELPER_HPP

// Wallet Helper: whelper

// system
#include <limits>
#include <sstream>
#include <vector>

// neo core
#include <ProtocolSettings.hpp>
#include <crypto/chelper.hpp>
#include <crypto/ICrypto.h>
#include <numbers/UInt160.hpp>
#include <system/Buffer.hpp>
#include <system/types.h>
#include <system/vhelper.hpp>
#include <wallets/KeyPair.hpp>

namespace neopt {

// wallets helper class
class whelper
{
public:
   static string ToAddress(const ProtocolSettings& settings, const UInt160& scriptHash)
   {
      vbyte data(21);
      data[0] = settings.AddressVersion;
      Buffer::BlockCopy(scriptHash.ToArray(), 0, data, 1, 20);
      return chelper::Base58CheckEncode(data);
   }

   static UInt160 ToScriptHash(const ProtocolSettings& settings, string& address)
   {
      vbyte data = chelper::Base58CheckDecode(address);
      if (data.size() != 21)
         NEOPT_EXCEPTION("Format Exception ToScriptHash");
      if (data[0] != settings.AddressVersion)
         NEOPT_EXCEPTION("Format Exception ToScriptHash");
      return UInt160(vhelper::Skip(data, 1));
   }
};

// TODO: define all operators here that are necessary

}

#endif
