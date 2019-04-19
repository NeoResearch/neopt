#ifndef IPLUGIN_H
#define IPLUGIN_H

// system includes
#include<vector>
#include<string>

// core includes
// ... none

namespace neopt
{

class IPlugin
{
public:
   // what to put here?

public: // TODO: make friend of PluginSystem? (protect?)

   // TODO: check if void* is better than string vector
   virtual bool OnMessage(const std::vector<std::string>& message) = 0;

   virtual std::string Name() const = 0;
};

}

#endif
