#ifndef BLOCK_HPP
#define BLOCK_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<system/ISerializable.h>
#include<system/IEquatable.h>
#include<system/IComparable.h>
#include<IInventory.h>
#include<numbers/UIntBase.hpp>
#include<numbers/BigInteger.h>
#include<system/shelper.h>
//#include<Transaction.hpp>

namespace neopt
{

   class Block : public IEquatable<Block>//, public IInventory
   {
   public:
      // TODO: finally fill here with transaction info

      bool Equals(const Block* other)
      {
         if(other == nullptr)
            return false;
         // (other == nullptr ? false : CompareTo(*other) == 0) // TODO: make shorter?
         return false;//CompareTo(*other) == 0;
      }
   };
}

#endif
