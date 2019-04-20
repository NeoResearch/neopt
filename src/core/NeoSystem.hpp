#ifndef NEO_SYSTEM_HPP
#define NEO_SYSTEM_HPP

// system includes
#include<vector>

// core includes
#include<plugin/IPlugin.h>
#include<plugin/PluginSystem.hpp>
#include<IBlockchain.h>


namespace neopt
{

// forward declaration of PluginSystem
class PluginSystem;

// TODO: NeoSystem may need to be a templated class, to fix forward declarations (NeoSystem<PluginSystem, Blockchain ,...>)
// TODO: another option may be to template all systems (PluginSystem<NeoSystem>...), less compromising but less powerful

class NeoSystem
{
public:
   PluginSystem& pluginSystem;

   IBlockchain& blockchain;

   NeoSystem(PluginSystem& _pluginSystem, IBlockchain& _blockchain) :
      pluginSystem(_pluginSystem), blockchain(_blockchain)
   {
      pluginSystem.neoSystem = this;
   }

   // what to put here?

};

}

#endif
