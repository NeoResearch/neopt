
// system includes
#include<iostream>

// core includes
#include<ledger/NeoSystem.h>
#include<ledger/plugin/PluginSystem.h>
//#include<core/wallets/Wallet.h>

// ledger includes
#include<ledger/Blockchain.hpp>

// internal includes
#include<shell/MainService.hpp>

// plugins
#include<plugins/ImportBlocks/ImportBlocks.h>

using namespace std;
using namespace neopt;

//Wallet wallet;

int main(int argc, char* argv[])
{
   // initialize plugin system
   PluginSystem pluginSystem;

   // initialize Blockchain ledger
   Blockchain blockchain;

   // build NeoSystem
   NeoSystem neoSystem(pluginSystem, blockchain);

   // manually loading "default" plugins (TODO: could use dynamic libraries)
   ImportBlocks pluginIB;
   pluginSystem.load(pluginIB);

   cout << "IB plugin: " << pluginIB.Name() << endl;

   // finished loading plugins
   pluginSystem.NotifyPluginsLoadedAfterSystemConstructed();


   // build MainService (cli)
   MainService mainService(pluginSystem);

   // process command-line arguments
   vector<string> args(argc);
   for(unsigned i=0; i<argc; i++)
      args[i] = argv[i];

   // run main service
   mainService.Run(args);

   // free resources
   ImportBlocksSettings::FreeSettings();

   // finished
   std::cout << "neopt-cli2 finished successfully" << std::endl;
   return 0;
}
