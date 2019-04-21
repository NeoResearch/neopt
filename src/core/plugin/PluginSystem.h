#ifndef PLUGIN_SYSTEM_H
#define PLUGIN_SYSTEM_H

// WARNING: do not include .hpp here, or things may break!

// system includes
#include<vector>
#include<string>

// core includes
#include<NeoSystem.h>
#include<system/types.h>
#include<plugin/LogLevel.h>
//#include<system/IConfigurationSection.h> // TODO: perhaps not good .hpp here

/*
#include<plugin/IPlugin.h>
#include<plugin/ILogPlugin.h>
#include<plugin/LogLevel.h>
*/



namespace neopt
{

// forward declaration
class IPlugin;
class ILogPlugin;

class PluginSystem
{
public:

   neopt::NeoSystem* neoSystem;

   std::vector<IPlugin*> Plugins;

   // specific plugins
   std::vector<ILogPlugin*> Loggers;

   std::string Path;

   PluginSystem(std::string path = "");

   // TODO: check better ways to do this (perhaps dynamic library?)
   // general plugin loading
   // TODO: must not delete this from memory
   void load(IPlugin& plugin);

   /*
   // TODO: must delete this from memory
   void load(IPlugin* plugin)
   {
      Plugins.push_back(plugin);

   }
   */

   // load plugins (TODO: load as dynamic library)
   void LoadPlugins();

   // TODO: implement this feature only on non-portable versions
   //static void FileSystemWatcherFolderChanged();
   /*
   void ReloadConfigurations()
   {
      for(unsigned i=0; i<Plugins.size(); i++)
      {
         Plugins[i]->Configure();
         stringstream ss;
         ss << "Reloaded config for " << Plugins[i]->Name();
         plugin.Log(ss.str());
         break; // TODO: why break?
      }
   }
   */

   bool SendMessage(const std::vector<std::string>& message);

   void NotifyPluginsLoadedAfterSystemConstructed();

public:
   void Log(const std::string& source, LogLevel level, const std::string& message);

};

}

#endif
