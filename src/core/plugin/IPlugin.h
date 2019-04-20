#ifndef IPLUGIN_H
#define IPLUGIN_H

// system includes
#include<iostream>
#include<vector>
#include<string>

// core includes
#include<plugin/LogLevel.h>

namespace neopt
{

class IPlugin
{
public:
   // what to put here?

public: // TODO: make friend of PluginSystem? (protect?)

   // TODO: check if void* is better than string vector
   virtual bool OnMessage(const std::vector<std::string>& message) = 0;

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
