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

class NeoSystem
{
public:
   PluginSystem& pluginSystem;

   IBlockchain& blockchain;

   NeoSystem(PluginSystem& _pluginSystem, IBlockchain& _blockchain) :
      pluginSystem(_pluginSystem), blockchain(_blockchain)
   {
   }

   // what to put here?

};

}

#endif
