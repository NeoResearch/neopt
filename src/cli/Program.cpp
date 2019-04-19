
// system includes
#include<iostream>

// core includes
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

   ImportBlocks pluginIB;
   pluginSystem.load(pluginIB);

   MainService mainService(pluginSystem);

   vector<string> args(argc);
   for(unsigned i=0; i<argc; i++)
      args[i] = argv[i];

   // run main service
   mainService.Run(args);

   std::cout << "neopt-cli finished successfully" << std::endl;
   return 0;
}
