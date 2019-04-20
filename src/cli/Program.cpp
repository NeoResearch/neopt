
// system includes
#include<iostream>

// core includes
#include<core/NeoSystem.hpp>
#include<core/plugin/PluginSystem.hpp>
//#include<core/wallets/Wallet.h>

// internal includes
#include<shell/MainService.hpp>

// plugins
#include<plugins/ImportBlocks/ImportBlocks.h>

using namespace std;
using namespace neopt;

//Wallet wallet;

int main(int argc, char* argv[])
{
   PluginSystem pluginSystem;

   // manually loading "default" plugins (TODO: could use dynamic libraries)
   ImportBlocks pluginIB;
   pluginSystem.load(pluginIB);

   // finished loading plugins
   pluginSystem.NotifyPluginsLoadedAfterSystemConstructed();

   // build NeoSystem
   NeoSystem neoSystem(pluginSystem);

   // build MainService (cli)
   MainService mainService(pluginSystem);

   // process command-line arguments
   vector<string> args(argc);
   for(unsigned i=0; i<argc; i++)
      args[i] = argv[i];

   // run main service
   mainService.Run(args);

   // finished
   std::cout << "neopt-cli finished successfully" << std::endl;
   return 0;
}
