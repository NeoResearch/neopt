#ifndef IBLOCKCHAIN_HPP
#define IBLOCKCHAIN_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <core/IScriptContainer.h>
#include <core/ISnapshot.h>
#include <system/ISerializable.h>

#include <Witness.hpp>
#include <crypto/ICrypto.h>
#include <numbers/UInt160.hpp>
#include <ledger/payloads/Block.hpp>
#include <wallets/KeyPair.hpp>

// TODO: fix, this .h should never include .hpp

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt {

class IBlockchain
{
private:
   ISnapshot* currentSnapshot;

public:
   // TODO: move singleton to Blockchain implementation, this is just an interface
   /*
   static IBlockchain* _singleton;

   static IBlockchain& Singleton()
   {
      return *_singleton;
   }
*/

   IBlockchain()
     : currentSnapshot(nullptr)
   {
   }

   virtual uint Height()
   {
      if (!currentSnapshot)
         return 0; // TODO: fix this
      return currentSnapshot->Height;
   }

   // method to import blocks
   virtual void OnImport(std::vector<Block>& blocks) = 0;
};

}

#endif
