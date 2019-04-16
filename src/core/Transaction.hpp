#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<system/ISerializable.h>
#include<system/IEquatable.h>
#include<system/IComparable.h>
#include<numbers/UIntBase.hpp>
#include<system/shelper.h>

namespace neopt
{

   class Transaction : public IEquatable<Transaction>, public IInventory
   {
   public:
      // TODO: finally fill here with transaction info
      
      bool Equals(const Transaction* other)
      {
         if(other == nullptr)
            return false;
         // (other == nullptr ? false : CompareTo(*other) == 0) // TODO: make shorter?
         return false;//CompareTo(*other) == 0;
      }
   };
}

#endif
