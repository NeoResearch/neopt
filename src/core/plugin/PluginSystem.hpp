#ifndef PLUGIN_SYSTEM_HPP
#define PLUGIN_SYSTEM_HPP

// system includes
#include<vector>

// core includes
#include<plugin/IPlugin.h>

namespace neopt
{

class PluginSystem
{
public:
   std::vector<IPlugin*> Plugins;

   // TODO: check better ways to do this (perhaps dynamic library?)
   // general plugin loading
   void load(IPlugin& plugin)
   {
      Plugins.push_back(&plugin);
   }

   bool SendMessage(const std::vector<std::string>& message)
   {
      for(unsigned i=0; i<Plugins.size(); i++)
         if (Plugins[i]->OnMessage(message))
            return true;
      return false;
   }
};

}

#endif
