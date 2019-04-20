#ifndef NEO_SYSTEM_HPP
#define NEO_SYSTEM_HPP

// system includes
#include<vector>

// core includes
#include<plugin/IPlugin.h>
#include<plugin/PluginSystem.hpp>


namespace neopt
{

class NeoSystem
{
public:
   // creating PluginSystem here
   PluginSystem& pluginSystem;

   NeoSystem(PluginSystem& _pluginSystem) :
      pluginSystem(_pluginSystem)
   {
   }

   // what to put here?

};

}

#endif
