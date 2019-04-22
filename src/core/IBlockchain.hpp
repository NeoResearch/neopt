#ifndef IBLOCKCHAIN_HPP
#define IBLOCKCHAIN_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<system/ISerializable.h>
#include<IScriptContainer.h>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt160.hpp>
#include<Witness.hpp>
#include<wallets/KeyPair.hpp>
#include<crypto/ICrypto.h>
#include<Block.hpp>

// TODO: fix, this .h should never include .hpp

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class IBlockchain
{
public:

// TODO: move singleton to Blockchain implementation, this is just an interface
/*
   static IBlockchain* _singleton;

   static IBlockchain& Singleton()
   {
      return *_singleton;
   }
*/

   int Height;


   // method to import blocks
   virtual void OnImport(std::vector<Block>& blocks) = 0;

};

}

#endif
