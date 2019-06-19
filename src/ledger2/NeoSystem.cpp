#include "NeoSystem.h"

// forward declaration
#include <ledger2/plugin/PluginSystem.h>

using namespace std;
using namespace neopt;

NeoSystem::NeoSystem(PluginSystem& _pluginSystem, IBlockchain& _blockchain)
  : pluginSystem(_pluginSystem)
  , blockchain(_blockchain)
{
   pluginSystem.neoSystem = this;
}
