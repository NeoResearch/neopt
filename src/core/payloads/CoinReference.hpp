#ifndef COIN_REFERENCE_HPP
#define COIN_REFERENCE_HPP

// c++ standard part
#include<vector>
#include<ostream>
#include<sstream>

// neopt core part
#include<system/ISerializable.h>
#include<IScriptContainer.h>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt160.hpp>
#include<Witness.hpp>
#include<wallets/KeyPair.hpp>
#include<crypto/Crypto.h>

#include<system/IBinaryWriter.h>


namespace neopt
{

// WARNING: escaping from the "Diamond of Death"
// making ISerializable a virtual inheritance
class CoinReference //: public ISerializable
{
public:

   virtual void Serialize(IBinaryWriter& writer) const
   {
   }

};

}

#endif
