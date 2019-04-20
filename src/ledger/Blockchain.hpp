#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<core/IBlockchain.h>
#include<core/NeoSystem.hpp>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class Blockchain : public IBlockchain
{
public:


   // method to import blocks
   void OnImport(std::vector<Block>& blocks)
   {

   }



};

}

#endif
