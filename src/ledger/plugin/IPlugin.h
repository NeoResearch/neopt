#ifndef IPLUGIN_H
#define IPLUGIN_H

// system includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// core includes
#include <ledger/plugin/LogLevel.h>
#include <ledger/plugin/PluginSystem.h>
#include <system/ConfigurationSection.hpp>

namespace neopt {

class IPlugin
{
public:
   // what to put here?
   PluginSystem* pluginSystem;

public: // TODO: make friend of PluginSystem? (protect?)
   virtual void Configure() = 0;

   // TODO: check if void* is better than string vector
   virtual bool OnMessage(const std::vector<std::string>& message) = 0;

   virtual std::string getConfigPath()
   {
      if (!pluginSystem || pluginSystem->Path == "")
         return "";
      std::stringstream ss;
      ss << pluginSystem->Path << "/" << Name() << "/"
         << "config.json";
      return ss.str();
   }

   ConfigurationSection GetConfiguration()
   {
      return ConfigurationSection::AddJsonBuild(getConfigPath(), true).GetSection("PluginConfiguration");
   }

protected:
public:
   IPlugin()
     : pluginSystem(nullptr)
   {
   }

   virtual void OnPluginsLoaded()
   {
   }

   virtual std::string Name() const = 0;

   // TODO: why is this Log necessary?
   // General Log (initially avoiding name hiding)
   virtual void GLog(std::string& message, LogLevel level = LogLevel::Info)
   {
      std::cout << Name() << " " << level << " " << message << std::endl;
   }
};

}

#endif
