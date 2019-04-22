#ifndef IINVENTORY_HPP
#define IINVENTORY_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<IVerifiable.hpp>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt256.hpp>
#include<InventoryType.h>

namespace neopt
{

class IInventory : public IVerifiable
{
public:

   virtual UInt256 getHash() = 0;

   virtual InventoryType getInventoryType() = 0;

   virtual bool Verify(ISnapshot& snapshot) = 0;
};

}

#endif
