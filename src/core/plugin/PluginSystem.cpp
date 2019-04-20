#include<plugin/PluginSystem.h>

// forward declarations
#include<plugin/IPlugin.h>
#include<plugin/ILogPlugin.h>

using namespace std;
using namespace neopt;

void PluginSystem::load(IPlugin& plugin)
{
   Plugins.push_back(&plugin);
   plugin.pluginSystem = this;
}

void PluginSystem::LoadPlugins()
{
   NEOPT_EXCEPTION("not implemented LoadPlugins from dynamic libraries");
}

bool PluginSystem::SendMessage(const std::vector<std::string>& message)
{
   for(unsigned i=0; i<Plugins.size(); i++)
      if (Plugins[i]->OnMessage(message))
         return true;
   return false;
}

void PluginSystem::NotifyPluginsLoadedAfterSystemConstructed()
{
    for(unsigned i=0; i<Plugins.size(); i++)
        Plugins[i]->OnPluginsLoaded();
}

void PluginSystem::Log(const std::string& source, LogLevel level, const std::string& message)
{
    for(unsigned i=0; i<Loggers.size(); i++)
        Loggers[i]->Log(source, level, message);
}
