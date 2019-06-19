#ifndef IINVENTORY_HPP
#define IINVENTORY_HPP

// c++ standard part
#include <vector>

// neopt core part
#include "ISnapshot.h" // remove if possible
#include "IVerifiable.hpp"

#include "InventoryType.h"
#include <numbers/UInt256.hpp>

namespace neopt {

class IInventory : public IVerifiable
{
public:
   virtual UInt256 getHash() = 0;

   virtual InventoryType getInventoryType() = 0;

   virtual bool Verify(ISnapshot& snapshot) = 0;
};

} // namespace neopt

#endif
