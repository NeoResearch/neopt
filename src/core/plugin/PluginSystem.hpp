#ifndef PLUGIN_SYSTEM_HPP
#define PLUGIN_SYSTEM_HPP

// system includes
#include<vector>

// core includes
#include<plugin/IPlugin.h>
#include<plugin/ILogPlugin.h>
#include<plugin/LogLevel.h>

namespace neopt
{


class PluginSystem
{
public:
   std::vector<IPlugin*> Plugins;

   // specific plugins
   std::vector<ILogPlugin*> Loggers;


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

protected:
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
