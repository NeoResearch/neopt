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
   IT_TX = 0x01,
   IT_Block = 0x02, // name conflict with Block class... beware!
   IT_Consensus = 0xe0
};

}

#endif
