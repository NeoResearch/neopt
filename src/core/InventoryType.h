#ifndef INVENTORY_TYPE_H
#define INVENTORY_TYPE_H

// c++ standard part
// none

// neopt core part
// ... none

namespace neopt
{

enum InventoryType // int, not byte
{
   TX = 0x01,
   Block = 0x02,
   Consensus = 0xe0
};

}

#endif
