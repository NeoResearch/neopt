#ifndef IBLOCKCHAIN_H
#define IBLOCKCHAIN_H



// c++ standard part
#include<vector>

// neopt core part
#include<system/ISerializable.h>
#include<IScriptContainer.h>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt160.hpp>
#include<Witness.h>
#include<wallets/KeyPair.hpp>
#include<crypto/ICrypto.h>
#include<Block.hpp>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class IBlockchain
{
public:


   // method to import blocks
   virtual void OnImport(std::vector<Block>& blocks) = 0;

};

}

#endif
