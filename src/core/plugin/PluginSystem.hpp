#ifndef PLUGIN_SYSTEM_HPP
#define PLUGIN_SYSTEM_HPP

// system includes
#include<vector>

// core includes
#include<system/types.h>
#include<plugin/IPlugin.h>
#include<plugin/ILogPlugin.h>
#include<plugin/LogLevel.h>

#include<NeoSystem.hpp>

namespace neopt
{

// forward declaration
class NeoSystem;

class PluginSystem
{
public:

   NeoSystem* neoSystem;

   std::vector<IPlugin*> Plugins;

   // specific plugins
   std::vector<ILogPlugin*> Loggers;


   // TODO: check better ways to do this (perhaps dynamic library?)
   // general plugin loading
   // TODO: must not delete this from memory
   void load(IPlugin& plugin)
   {
      Plugins.push_back(&plugin);
      plugin.pluginSystem = this;
   }

   /*
   // TODO: must delete this from memory
   void load(IPlugin* plugin)
   {
      Plugins.push_back(plugin);

   }
   */

   // load plugins (TODO: load as dynamic library)
   void LoadPlugins()
   {
      NEOPT_EXCEPTION("not implemented LoadPlugins from dynamic libraries");
   }

   bool SendMessage(const std::vector<std::string>& message)
   {
      for(unsigned i=0; i<Plugins.size(); i++)
         if (Plugins[i]->OnMessage(message))
            return true;
      return false;
   }

   void NotifyPluginsLoadedAfterSystemConstructed()
   {
       for(unsigned i=0; i<Plugins.size(); i++)
           Plugins[i]->OnPluginsLoaded();
   }

public:
   void Log(const std::string& source, LogLevel level, const std::string& message)
   {
       for(unsigned i=0; i<Loggers.size(); i++)
           Loggers[i]->Log(source, level, message);
   }
};

}

#endif
