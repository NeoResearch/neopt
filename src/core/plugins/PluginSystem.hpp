#ifndef PLUGIN_SYSTEM_HPP
#define PLUGIN_SYSTEM_HPP

// system includes
#include<vector>

// core includes
#include<plugins/IPlugin.h>

namespace neopt
{

class PluginSystem
{
public:
   std::vector<IPlugin> plugins;

   bool SendMessage(const std::vector<std::string>& args)
   {
      return false;
   }
};

}

#endif
