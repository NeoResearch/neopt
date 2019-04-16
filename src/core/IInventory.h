#ifndef IINVENTORY_H
#define IINVENTORY_H

// c++ standard part
#include<vector>

// neopt core part
#include<IVerifiable.h>
#include<ISnapshot.h> // TODO: remove if possible

#include<numbers/UInt256.hpp>
#include<InventoryType.h>

using namespace std; // TODO: do not use that in the future... prefer std::vector instead

namespace neopt
{

class IInventory : public IVerifiable
{
public:

   virtual UInt256 getHash() = 0;

   virtual InventoryType getInventoryType() = 0;

   virtual bool Verify(ISnapshot snapshot) = 0;
};

}

#endif
