#ifndef ILOG_PLUGIN_H
#define ILOG_PLUGIN_H

// system includes
#include<iostream>
#include<vector>
#include<string>

// core includes
#include<plugin/LogLevel.h>

namespace neopt
{

class ILogPlugin : public IPlugin
{
public:
   // what to put here?

public: // TODO: make friend of PluginSystem? (protect?)

   virtual void Log(const std::string& source,  LogLevel level, const std::string& message) = 0;
};

}

#endif