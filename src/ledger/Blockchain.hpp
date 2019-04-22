#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<core/IBlockchain.hpp>
#include<core/NeoSystem.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class Blockchain : public IBlockchain
{
public:

   // TODO: avoid singleton for now
   /*
   // Singleton Class (TODO: use pattern on inheritance)
   static IBlockchain* _singleton;

   static IBlockchain& Singleton()
   {
      return *_singleton;
   }
   */



   // method to import blocks
   void OnImport(std::vector<Block>& blocks)
   {

   }



};

}

#endif
