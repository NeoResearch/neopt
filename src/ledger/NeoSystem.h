#ifndef NEO_SYSTEM_H
#define NEO_SYSTEM_H

// WARNING: do not include .hpp here, or things may break!

// system includes
#include <vector>

// core includes
//#include<plugin/IPlugin.h>

namespace neopt {

// forward declaration of PluginSystem
class PluginSystem;

// forward declaration of IBlockchain
class IBlockchain;

// TODO: NeoSystem may need to be a templated class, to fix forward declarations (NeoSystem<PluginSystem, Blockchain ,...>)
// TODO: another option may be to template all systems (PluginSystem<NeoSystem>...), less compromising but less powerful

class NeoSystem
{
public:
   PluginSystem& pluginSystem;

   IBlockchain& blockchain;

   NeoSystem(PluginSystem& _pluginSystem, IBlockchain& _blockchain);

   // what to put here?
};

}

#endif
